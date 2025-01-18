#pragma once

#include "Core/Assert.h"

#ifdef CL_PLATFORM_WINDOWS
	#include <Windows.h>
#elif defined CL_PLATFORM_LINUX
	#include <linux/limits.h>
	#include <unistd.h>
#endif

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <filesystem>
#include <functional>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include <thread>
#include <atomic>
#include <mutex>
#include <regex>
#include <array>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <any>
#include <new>
