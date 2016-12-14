/*
 * Copyright 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "actions.h"

#include <memory> // std::shared_ptr
#include <vector>

#include <gio/gio.h> // GMenuModel

namespace unity {
namespace indicator {
namespace printers {

/**
 * \brief A menu for a specific profile; eg, Desktop or Phone.
 *
 * @see MenuFactory
 * @see Exporter
 */
class Menu
{
public:
    enum Profile { Desktop, DesktopGreeter, Phone, PhoneGreeter, NUM_PROFILES };
    const std::string& name() const;
    Profile profile() const;
    GMenuModel* menu_model();

protected:
    Menu (Profile profile_in, const std::string& name_in);
    virtual ~Menu() = default;
    GMenu* m_menu = nullptr;

private:
    const Profile m_profile;
    const std::string m_name;

    // we've got raw pointers in here, so disable copying
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};

/**
 * \brief Builds a Menu for a given state and profile
 *
 * @see Menu
 * @see Exporter
 */
class MenuFactory
{
public:
    MenuFactory (const std::shared_ptr<Actions>& actions);
    std::shared_ptr<Menu> buildMenu(Menu::Profile profile);

private:
    std::shared_ptr<Actions> m_actions;
};

} // namespace printers
} // namespace indicator
} // namespace unity