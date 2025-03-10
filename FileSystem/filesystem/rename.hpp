/**
 * @file rename.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <common.hpp>
#include <attributes.hpp>

#include <string>

namespace is
{
    namespace common
    {
        namespace detail
        {
#if defined(_WIN32) || defined(_WIN64)

#if defined(_UNICODE) || defined(UNICODE)
            inline bool
            __rename(const std::string &oldname, const std::string &newname)
            {
                bool ret = false;
                std::wstring oldnameL = is::common::cvt_shiftjis_to_utf16(oldname);
                std::wstring newnameL = is::common::cvt_shiftjis_to_utf16(newname);
                int stat = _wrename(oldnameL.c_str(), newnameL.c_str());
                if (stat == 0) // newnameと重複するファイル名, ディレクトリ名が存在する場合失敗する.
                {
                    ret = true;
                }
                return ret;
            }
#else
            inline bool
            __rename(const std::string &oldname, const std::string &newname)
            {
                bool ret = false;
                int stat = ::rename(oldname.c_str(), newname.c_str());
                if (stat == 0) // newnameと重複するファイル名, ディレクトリ名が存在する場合失敗する.
                {
                    ret = true;
                }
                return ret;
            }
#endif

#elif defined(__linux__) || defined(__MACH__)
            inline bool
            __rename(const std::string &oldname, const std::string &newname)
            {
                // macOS, Linux(Ubuntu)ではデフォルトで上書き設定なので, 
                // newnameが既に存在する場合, 失敗とする.
                bool stat_ret = isexist(newname);
                if (stat_ret)
                {
                    return false;
                }
                bool ret = false;
                int stat = ::rename(oldname.c_str(), newname.c_str());
                if (stat == 0)
                {
                    ret = true;
                }
                return ret;
            }
#else
#error "Not match platform"
#endif
        }

        inline bool 
        rename(const std::string& oldname, const std::string& newname)
        {
            return detail::__rename(oldname, newname);
        }
    }
}