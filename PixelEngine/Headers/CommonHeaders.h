#pragma once
//sfml
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
//sfml tgui
#include<TGUI/TGUI.hpp>
#include<TGUI/Backend.hpp>
//io
#include<iostream>
#include<fstream>
//containers
#include<list>
#include<vector>
#include<map>
#include<set>
//threading
#include<mutex>
#include<thread>
#include<condition_variable>
#include<future>
//object managment
#include<optional>
#include<memory>
//other
#include<utility>
#include<string>
#include<exception>
#include<random>
#include<algorithm>
#include<chrono>
//json
#include "json.hpp"

using json = nlohmann::json;