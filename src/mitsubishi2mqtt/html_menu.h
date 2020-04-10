/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2019 gysmo38, dzungpv, shampeon, endeavour, jascdk, chrdavis, alekslyse.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
 
const char html_menu_root[] PROGMEM = R"====(
<style>
    #control div {
        padding: 0;
        text-align: center;
    }
    #control div [data-options] {
        margin: 10px 0;
    }
    #control .button {
        color: transparent;  
        text-shadow: 0 0 0 #eaeaea;
        width: 38px;
        border-radius: 50%;
    }
</style>
<div id="control" data-if="connected" style="display:none">
    <div>
        <h1>
            <span class="button" onclick="st(1)">+</span>
            <span id="temperture"></span>
            <span class="button" onclick="st(-1)">-</span>
        </h1>
        <h3>room temperture: <span id="room_temperture"></span></h3>
    </div>
    <div data-if="power">
        <div data-options="mode">
            <h3>Mode</h3>
            <span class="button bred" onclick="la('POWER=OFF')" title="off">&#128268;</span>
            <span class="button" data-selected='AUTO' onclick="la('MODE=AUTO')" title="auto">&#9851;</span>
            <span class="button" data-selected='DRY' onclick="la('MODE=DRY')" title="dry">&#128167;</span>
            <span class="button" data-selected='COOL' onclick="la('MODE=COOL')" title="cool">&#10052;&#65039;</span>
            <span class="button" data-selected='HEAT' data-if="support_heat_mode" onclick="la('MODE=HEAT')" title="heat">&#9728;&#65039;</span>
            <span class="button" data-selected='FAN' onclick="la('MODE=FAN')" title="fan">&#10051;</span>
        </div>
        <div data-options="fan">
            <h3>Fan Speed</h3>
            <span class="button" data-selected='AUTO' onclick="la('FAN=AUTO')" title="auto">&#9851;</span>
            <span class="button" data-selected='QUIET' onclick="la('FAN=QUIET')" title="quiet">....</span>
            <span class="button" data-selected='1' onclick="la('FAN=1')" title="1">...|</span>
            <span class="button" data-selected='2' onclick="la('FAN=2')" title="2">..::</span>
            <span class="button" data-selected='3' onclick="la('FAN=3')" title="3">.:::</span>
            <span class="button" data-selected='4' onclick="la('FAN=4')" title="4">::::</span>
        </div>
        <div data-options="vane">
            <h3>Vane</h3>
            <span class="button" data-selected='AUTO' onclick="la('VANE=AUTO')" title="auto">&#9851;</span>
            <span class="button" data-selected='SWING' onclick="la('VANE=SWING')" title="swing">&#9887;</span>
            <span class="button" data-selected='1' onclick="la('VANE=1')" title="1">&#10143;</span>
            <span class="button" data-selected='2' onclick="la('VANE=2')" title="2">&#10143;</span>
            <span class="button" data-selected='3' onclick="la('VANE=3')" title="3">&#10143;</span>
            <span class="button" data-selected='4' onclick="la('VANE=4')" title="4">&#10143;</span>
            <span class="button" data-selected='5' onclick="la('VANE=5')" title="5">&#10143;</span>         
        </div>
        <div data-options="wide_vane">
            <h3>Wide Vane</h3>
            <span class="button" data-selected='AUTO' onclick="la('WIDEVANE=AUTO')" title="auto">&#9851;</span>
            <span class="button" data-selected='SWING' onclick="la('WIDEVANE=SWING')" title="swing">&#9887;</span>
            <span class="button" data-selected='<<' onclick="la('WIDEVANE=<<')" title="<<"><<</span>
            <span class="button" data-selected='<' onclick="la('WIDEVANE=<')" title="<"><</span>
            <span class="button" data-selected='|' onclick="la('WIDEVANE=|')" title="|">|</span>
            <span class="button" data-selected='>' onclick="la('WIDEVANE=>')" title=">">></span>
            <span class="button" data-selected='>>' onclick="la('WIDEVANE=>>')" title=">>">>></span>
            <span class="button" data-selected='<>' onclick="la('WIDEVANE=<>')" title="<>"><></span>
        </div>
    </div>
    <div data-if-not="power">
        <button id="false" onclick="la('POWER=ON')">Power On</span>
    </div>
</div>
<div>
    <form action='/setup' method='get'>
        <button>Setup</button>
    </form>
</div>
<div>
    <form action='/status' method='get'>
        <button>Status</button>
    </form>
</div>
<div>
    <form action='/upgrade' method='get'>
        <button>Firmware Upgrade</button>
    </form>
</div>
<div>
    <form>
        <button type='submit' name='REBOOT' class='button bred'>Reboot</button>
    </form>
</div>
<div id="logout" style="display:none">
    <form action='/login?LOGOUT=YES' method='post'>
        <button type='submit' name='Logout' class='button bred'>Logout</button>
    </form>
</div>
<script>
    if (_SHOW_LOGOUT_) {
        document.getElementById("logout").style.display = "";
    }
</script>
)====";


const char html_menu_setup[] PROGMEM = R"====(
<p>
    <form action='/mqtt' method='get'>
        <button>MQTT</button>
    </form>
</p>
<p>
    <form action='/wifi' method='get'>
        <button>WIFI</button>
    </form>
</p>
<p>
    <form action='/advance' method='get'>
        <button>ADVANCED</button>
    </form>
</p>
<p>
    <form>
        <button type='submit' name='RESET' class='button bred'>Reset configuration</button>
    </form>
</p>
<p>
    <form action='/' method='get'>
        <button>Back</button>
    </form>
</p>
)====";
