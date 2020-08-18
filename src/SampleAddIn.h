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

#ifndef SAMPLEADDIN_H
#define SAMPLEADDIN_H

#include "Component.h"

class SampleAddIn final : public Component {
public:
    const char *Version = u8"1.0.0";

    SampleAddIn();

private:
    std::string extensionName() override;

    variant_t add(const variant_t &a, const variant_t &b);

    void message(const variant_t &msg);

    void sleep(const variant_t &delay);

    void assign(variant_t &out);

    variant_t samplePropertyValue();

    variant_t currentDate();

    std::shared_ptr<variant_t> sample_property;
};

#endif //SAMPLEADDIN_H
