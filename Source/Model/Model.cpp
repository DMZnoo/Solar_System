#include "Model.hpp"

void Model::loadModel(char const* path,GLenum drawtype)
{
    drawType = drawtype;
    this->objpath = std::string(path);
   //this constructor is used when we have a model to load. Otherwise default is called
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene -> mRootNode)
    {
        std::cout << "Assimp Error: " << importer.GetErrorString() << std::endl;
        throw std::exception();
    }
    
    assembleModel(scene->mRootNode, scene);
    
}



void Model::assembleModel(aiNode *node, const aiScene *scene)
{
    for (unsigned int n = 0; n < node->mNumMeshes; n++)
    {
        
        aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];
        for(unsigned int x = 0; x < mesh->mNumVertices; x++)
        {
            Vertex vertex;
            glm::vec3 coor;
            
            coor.x = mesh->mVertices[x].x;

            coor.y = mesh->mVertices[x].y;
            coor.z = mesh->mVertices[x].z;
            
            vertex.Position = coor;
            
            coor.x = mesh->mNormals[x].x;
            coor.y = mesh->mNormals[x].y;
            coor.z = mesh->mNormals[x].z;
            
            vertex.Normal = coor;
            
            if(mesh->mTextureCoords[0])
            {
                glm::vec2 texCoords;
                
                texCoords.x = mesh->mTextureCoords[0][x].x;
                texCoords.y = mesh->mTextureCoords[0][x].y;
                vertex.TexCoords = texCoords;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f,0.0f);
            if(mesh->mTangents != NULL)
                {
                    coor.x = mesh->mTangents[x].x;
                    coor.y = mesh->mTangents[x].y;
                    coor.z = mesh->mTangents[x].z;
                    
                    vertex.Tangent = coor;
                }
            if(mesh->mBitangents != NULL)
                {
                    coor.x = mesh->mBitangents[x].x;
                    coor.y = mesh->mBitangents[x].y;
                    coor.z = mesh->mBitangents[x].z;
                    
                    vertex.Bitangent = coor;
                }
            

            m_mesh.vertices.push_back(vertex);
        }
        
        for(unsigned int y = 0; y < mesh -> mNumFaces; y++)
        {
            aiFace face = mesh -> mFaces[y];
            for(unsigned int z = 0; z < face.mNumIndices; z++)
            {
                m_mesh.indices.push_back(face.mIndices[z]);
            }
        }
        
        aiMaterial* material = scene -> mMaterials[mesh->mMaterialIndex];
        
        std::map< unsigned int, std::map<std::string,aiTextureType> > materialTexture;
        materialTexture[0]["texture_diffuse"] = aiTextureType_DIFFUSE;
        materialTexture[1]["texture_specular"] = aiTextureType_SPECULAR;
        materialTexture[2]["texture_normal"] = aiTextureType_HEIGHT;
        materialTexture[3]["texture_height"] = aiTextureType_AMBIENT;

        std::vector<Texture> textures;
        for(auto ptr = materialTexture.begin(); ptr != materialTexture.end(); ptr++)
        {
            
            for(auto it = ptr->second.begin(); it != ptr->second.end(); it++)
            {
                
                for(unsigned int a = 0; a < material -> GetTextureCount(it->second);a++)
                {
                    aiString path;
                    material -> GetTexture(it->second, a, &path);
//                    std::cout << path.C_Str() << std::endl;
                    
                    Texture texture;
                    size_t index = 0;
                    std::string temp = objpath.substr(ROOT.length(),objpath.length());
                    index = temp.find_last_of("/\\");
                    
//                    std::cout << IO_Util::concat(temp.substr(0,index) + "/" + std::string(path.C_Str())).c_str() << std::endl;
                    texture.textID = m_texture.LoadTexture(IO_Util::concat(temp.substr(0,index) + "/" + std::string(path.C_Str())).c_str());
                    texture.type = it->first;
                    texture.name = path.C_Str();
                    textures.push_back(texture);
                }
                
                m_mesh.textures.insert(m_mesh.textures.end(),textures.begin(),textures.end());
                std::vector<Texture>().swap(textures);
            }
        }
        
        bindMesh(&m_mesh);
        modelInfo.push_back(m_mesh);
        m_mesh.reset();
        
    }
    
    for(unsigned int i = 0; i < node -> mNumChildren; i++)
    {
        assembleModel(node->mChildren[i], scene);
    }
}

void Model::bindMesh(Mesh* mesh)
{
    genVAO();
    genVBO();
    bindVAO();
    bindVBO();
    
    GLCall(glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), mesh->vertices.data(), drawType));
    addIBO(mesh->indices);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
    
    
    
}




const std::vector<Mesh> &Model::getModelInfo()
{
    return modelInfo;
}


Model::~Model()
{
    drop();
}

Model::Model(Model &&other)
    : m_renderInfo(other.m_renderInfo)
    , m_vboCount(other.m_vboCount)
    , m_buffers(std::move(other.m_buffers))
{
    other.m_renderInfo.reset();
    other.m_vboCount = 0;
}

Model &Model::operator=(Model &&other)
{
    m_renderInfo = other.m_renderInfo;
    m_vboCount = other.m_vboCount;
    m_buffers = std::move(other.m_buffers);

    other.m_renderInfo.reset();
    other.m_vboCount = 0;

    return *this;
}

void Model::genVAO()
{
    GLCall(glGenVertexArrays(1, &m_renderInfo.vao));
    m_renderInfo.vao_list.push_back(m_renderInfo.vao);
}

void Model::genVBO()
{
    GLCall(glGenBuffers(1, &m_renderInfo.vbo));
    m_renderInfo.vbo_list.push_back(m_renderInfo.vbo);
}

void Model::genIBO()
{
    GLCall(glGenBuffers(1, &m_renderInfo.ibo));
    
}
void Model::genSBO()
{
    GLCall(glGenBuffers(1, &m_renderInfo.sbo));
    
}

void Model::bindVAO() const
{
    GLCall(glBindVertexArray(m_renderInfo.vao));
    
}

void Model::bindVBO() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderInfo.vbo));
}

void Model::bindIBO() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderInfo.ibo));
}

void Model::bindSBO(int size, const std::vector<glm::mat4> &data) const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderInfo.sbo));
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::mat4), data.data(), drawType);
}

void Model::addVBO(int dimensions,unsigned int stride, const std::vector<GLfloat> &data)
{

    genVBO();
    bindVBO();
    m_dim = dimensions;
    
    GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(),
                 drawType));
    GLCall(glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount)));
    GLCall(glVertexAttribPointer(static_cast<GLuint>(m_vboCount++), m_dim, GL_FLOAT,
                          GL_FALSE, stride*sizeof(float), (GLvoid *)0));
    m_buffers.push_back(m_renderInfo.vbo);
}

void Model::addAttribArray(int dimensions, unsigned int stride)
{
    
    GLCall(glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount)));
    GLCall(glVertexAttribPointer(static_cast<GLuint>(m_vboCount++), dimensions, GL_FLOAT,GL_FALSE, stride*sizeof(float), (void*)(m_dim * sizeof(float))));
    m_dim = dimensions;
    
}

void Model::addIBO(const std::vector<GLuint> &indices)
{
    genIBO();
    m_renderInfo.indicesCount = indices.size();
    m_renderInfo.ibo_list.push_back(m_renderInfo.indicesCount);
    bindIBO();
    
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                        indices.data(), drawType));
}
void Model::setType(GLenum type)
{
    drawType = type;
}
void Model::drop()
{
    
//    if (m_buffers.size() > 0)
  //      GLCall(glDeleteBuffers(static_cast<GLsizei>(m_buffers.size()),
    //                           m_buffers.data()));
    m_buffers.clear();
    m_mesh.reset();
    m_vboCount = 0;
    m_renderInfo.reset();
}

unsigned int Model::getIndicesCount() const
{
    return m_renderInfo.indicesCount;
}

const RenderInfo &Model::getRendererInfo() const
{
    return m_renderInfo;
}

void Model::addSBO(int size, const std::vector<glm::mat4> &data) { 
    genSBO();
    bindSBO(size,data);
    setInstanceModel();
}

void Model::setInstanceModel() const
{
    for(int i = 0; i < m_renderInfo.vao_list.size(); i++)
    {
            glBindVertexArray(m_renderInfo.vao_list[i]);
            // set attribute pointers for matrix (4 times vec4)
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
    }

}

