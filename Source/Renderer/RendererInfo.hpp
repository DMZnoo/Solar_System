//
//  RendererInfo.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 29/04/20.
//

#ifndef RendererInfo_hpp
#define RendererInfo_hpp

struct RenderInfo {
    unsigned int indicesCount = 0;
    unsigned int vao,vbo,ibo,sbo;
    std::vector<unsigned int> vao_list;
    std::vector<unsigned int> vbo_list;
    std::vector<unsigned int> ibo_list;

    inline void reset()
    {
        vao = 0;
        vbo = 0;
        ibo = 0;
        sbo = 0;
        std::vector<unsigned int>().swap(vao_list);
        std::vector<unsigned int>().swap(vbo_list);
        std::vector<unsigned int>().swap(ibo_list);
        indicesCount = 0;
    }
};

#endif /* RendererInfo_hpp */
