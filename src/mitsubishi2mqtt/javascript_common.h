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

const char common_script[] PROGMEM = 
"<script>"
    "function eid(id) {"
        "return document.getElementById(id)"
    "}"
"</script>"
;

const char count_down_script[] PROGMEM = 
"<script>"
    "var count = 10;"
    "(function countDown() {"
        "eid('count').innerHTML = count + 's';"
        "setTimeout(function() {"
            "if(count > 0) {"
                "count --;"
                "return countDown();"
            "} else {"
                "window.location.href = '/';"
            "}"
        "}, 1000);"
    "})();"
"</script>"
;

const char root_control_script[] PROGMEM = 
"<script>"
    "var x = null, lt, s;"
    "function qs(q){return document.querySelector(q)}"
    "function qsa(q){return [...document.querySelectorAll(q)]}"
    "function ap() {"
        "qsa('[data-if]').forEach(e => e.style.display = s[e.getAttribute('data-if')] ? '' : 'none');"
        "qsa('[data-if-not]').forEach(e => e.style.display = s[e.getAttribute('data-if-not')] ? 'none' : '');"
        "Object.keys(s).filter(eid).forEach(k => eid(k).innerHTML = `${s[k]}°`);"
        "Object.keys(s)"
            ".filter(k => qs(`[data-options=${k}]`))"
            ".forEach(k => {"
                "qsa(`[data-options=${k}] [data-selected]`).forEach(e => e.classList.remove('bgrn'));"
                "qs(`[data-options=${k}] [data-selected='${s[k]}']`).classList.add('bgrn')"
            "});"
    "}"
    "function st(t) {"
        "la('TEMP='+(s['temperture'] + t * s[temp_step]));"
    "}"
    "function la(p) {"
        "var a = '';"
        "if (la.arguments.length == 1) {"
            "a = p;"
            "clearTimeout(lt);"
        "}"
        "if (x != null) {"
            "x.abort();"
        "}"
        "x = new XMLHttpRequest();"
        "x.onreadystatechange = function() {"
            "if (x.readyState == 4 && x.status == 200) {"
                "s=x.response;"
                "ap();"
            "}"
        "};"
        "x.open('GET', './control?' + a, true);"
	    "x.responseType='json';"
        "x.send();"
        "lt = setTimeout(la, 2345);"
    "}"
    "la();"
"</script>"
;