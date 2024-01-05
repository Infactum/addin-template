/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <ComponentBase.h>
#include <types.h>

#include "SampleAddIn.h"

#ifdef _WINDOWS
#pragma warning (disable : 4311 4302)
#endif

const WCHAR_T *GetClassNames() {
    // Might contain multiple class names seperated by |
    static char16_t cls_names[] = u"Sample";
    return reinterpret_cast<WCHAR_T *>(cls_names);
}

long GetClassObject(const WCHAR_T *clsName, IComponentBase **pInterface) {
    if (!*pInterface) {
        auto cls_name = std::u16string(reinterpret_cast<const char16_t *>(clsName));
        if (cls_name == u"Sample") {
            *pInterface = new SampleAddIn;
        }
        return (long) *pInterface;
    }
    return 0;
}

long DestroyObject(IComponentBase **pInterface) {
    if (!*pInterface) {
        return -1;
    }

    delete *pInterface;
    *pInterface = nullptr;
    return 0;
}

AppCapabilities SetPlatformCapabilities(const AppCapabilities capabilities) {
    return eAppCapabilitiesLast;
}

AttachType GetAttachType() {
#if ATTACH_TYPE == ATTACH_TYPE_ANY
    return eCanAttachAny;
#elif ATTACH_TYPE == ATTACH_TYPE_ISOLATED
    return eCanAttachIsolated;
#elif ATTACH_TYPE == ATTACH_TYPE_NOT_ISOLATED
    return eCanAttachNotIsolated;
#else
#error "Unrecognized ATTACH_TYPE"
#endif
}