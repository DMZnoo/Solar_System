//
//  NonCopyable.hpp
//
//  Created by JINWOO LEE on 28/04/20.
//

#ifndef NonCopyable_hpp
#define NonCopyable_hpp

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator = (const NonCopyable &) = delete;
};

#endif /* NonCopyable_hpp */
