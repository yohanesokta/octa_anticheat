/* extension.js
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import GObject from 'gi://GObject';
import St from 'gi://St';
import Soup from 'gi://Soup?version=3.0';
import GLib from 'gi://GLib';
import Clutter from 'gi://Clutter';

import {Extension, gettext as _} from 'resource:///org/gnome/shell/extensions/extension.js';
import * as PanelMenu from 'resource:///org/gnome/shell/ui/panelMenu.js';
import * as Main from 'resource:///org/gnome/shell/ui/main.js';

const Indicator = GObject.registerClass(
class Indicator extends PanelMenu.Button {
    _init() {
        super._init(0.0, _('Octa Anticheat'));

        this.add_child(new St.Icon({
            icon_name: 'security-high-symbolic',
            style_class: 'system-status-icon',
        }));

        this.connect('button-press-event', () => {
            Main.notify('Octa Anticheat', 'Copyright 2026 Yohanes Oktanio');
        });
    }
});

export default class OctaAnticheatExtension extends Extension {
    enable() {
        this._indicator = new Indicator();
        Main.panel.addToStatusArea(this.uuid, this._indicator);

        this._startServer();
    }

    disable() {
        this._stopServer();
        this._indicator.destroy();
        this._indicator = null;
    }

    _startServer() {
        const startupId = Math.floor(Math.random() * 10000);
        console.log(`Octa Anticheat [${startupId}]: Starting server on port 9012`);
        
        try {
            this._server = new Soup.Server();
            
            this._server.add_handler('/status', (server, msg, path, query) => {
                try {
                    console.log(`Octa Anticheat [${startupId}]: Request /status`);
                    const window = global.display.get_focus_window();
                    const title = window ? window.get_title() : 'Unknown';
                    
                    const response = JSON.stringify({ active_window: title });
                    const bytes = new GLib.Bytes(response);
                    
                    msg.set_status(200, null);
                    msg.get_response_headers().append('Content-Type', 'application/json');
                    msg.get_response_body().append_bytes(bytes);
                    
                    console.log(`Octa Anticheat [${startupId}]: Response sent (${bytes.get_size()} bytes)`);
                } catch (err) {
                    console.error(`Octa Anticheat Handler Error: ${err}`);
                }
            });

            this._server.add_handler('/ping', (server, msg, path, query) => {
                try {
                    console.log(`Octa Anticheat [${startupId}]: Request /ping`);
                    const response = JSON.stringify({ message: 'pong' });
                    const bytes = new GLib.Bytes(response);
                    
                    msg.set_status(200, null);
                    msg.get_response_headers().append('Content-Type', 'application/json');
                    msg.get_response_body().append_bytes(bytes);
                    
                    console.log(`Octa Anticheat [${startupId}]: Response sent (${bytes.get_size()} bytes)`);
                } catch (err) {
                    console.error(`Octa Anticheat Handler Error: ${err}`);
                }
            });

            this._server.listen_local(9012, Soup.ServerListenOptions.NONE);
            console.log(`Octa Anticheat [${startupId}]: Server is UP at http://localhost:9012`);
        } catch (e) {
            console.error(`Octa Anticheat [${startupId}]: Fatal Error: ${e.message}`);
        }
    }

    _stopServer() {
        if (this._server) {
            console.log('Octa Anticheat: Stopping server');
            // Remove handlers to help cleanup
            this._server.remove_handler('/status');
            this._server.remove_handler('/ping');
            this._server = null;
        }
    }
}
