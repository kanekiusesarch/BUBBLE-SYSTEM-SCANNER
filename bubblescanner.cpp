#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdio>
#include <array>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cstring>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <intrin.h>
#else
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <unistd.h>
#endif

using namespace std;

// ANSI color codes
const string RED = "\033[1;31m";
const string YELLOW = "\033[1;33m";
const string GREEN = "\033[1;32m";
const string CYAN = "\033[1;36m";
const string MAGENTA = "\033[1;35m";
const string BLUE = "\033[1;34m";
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string BLINK = "\033[5m";

// Helpers
string trim(const string &s) {
    auto start = s.find_first_not_of("\t\n\r ");
    auto end = s.find_last_not_of("\t\n\r ");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

string random_msg(const vector<string> &msgs) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(0, msgs.size()-1);
    return msgs[dist(gen)];
}

// Run shell command and capture output
string run_command(const string& cmd) {
    array<char, 128> buffer;
    string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return trim(result);
}

// Convert bytes to human-readable format
string human_bytes(uint64_t bytes) {
    const char* suffixes[5] = {"B", "KB", "MB", "GB", "TB"};
    double count = bytes;
    int i = 0;
    while(count >= 1024 && i < 4) {
        count /= 1024;
        i++;
    }
    stringstream ss;
    ss.precision(2);
    ss << fixed << count << " " << suffixes[i];
    return ss.str();
}

void super_ascii_logo() {
    cout << MAGENTA << BOLD;
    cout << R"(
   _____                       _____                 _                 
  / ____|                     / ____|               | |                
 | (___  _   _ _ __ ___  ___ | (___  _   _ _ __   __| | ___  _ __ ___  
  \___ \| | | | '__/ _ \/ __| \___ \| | | | '_ \ / _` |/ _ \| '__/ _ \ 
  ____) | |_| | | |  __/\__ \ ____) | |_| | | | | (_| | (_) | | |  __/ 
 |_____/ \__, |_|  \___||___/|_____/ \__,_|_| |_|\__,_|\___/|_|  \___| 
           __/ |                                                        
          |___/                                                         

         SUPER SYSTEM SCANNER v1.0
    )" << RESET << "\n";
}

void display_status(const string &label, const string &value, const string &color=CYAN) {
    cout << color << label << ": " << value << RESET << "\n";
}

string get_platform() {
#if defined(_WIN32) || defined(_WIN64)
    return "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
    return "macOS";
#elif defined(__linux__)
    return "Linux";
#elif defined(__unix__)
    #ifdef __FreeBSD__
        return "FreeBSD";
    #elif defined(__NetBSD__)
        return "NetBSD";
    #elif defined(__OpenBSD__)
        return "OpenBSD";
    #elif defined(__minix)
        return "Minix";
    #else
        return "Unix";
    #endif
#else
    return "DOS / Unknown";
#endif
}

void fun_animations() {
    vector<string> frames = {"(o_o)", "(O_O)", "(0_0)", "(^_^)"};
    for(int i=0;i<8;i++) {
        cout << "\rSuper scanning... " << frames[i%frames.size()] << flush;
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    cout << "\r                      \r";
}

int main() {
    ios::sync_with_stdio(false);

    super_ascii_logo();

    cout << MAGENTA << "Made by kaneki | https://github.com/kanekiusesarch" << RESET << "\n\n";

    string platform = get_platform();
    display_status("[PLATFORM DETECTED]", platform, BLUE);

    cout << CYAN << "==============================\n" << RESET;
    cout << "   Activating Super Bubble Engine... 🚀\n";
    cout << CYAN << "==============================\n\n" << RESET;

    fun_animations();

    vector<vector<string>> stage_msgs = {
        {"SUPER BUBBLE is poking the CPU... 🤏", "SUPER Bubble flexing CPU muscles... 💪", "SUPER Bubble tickling the processor... 😜"},
        {"SUPER BUBBLE is bubbling memory checks... 🫧", "SUPER Bubble juggling memory sticks... 🤹", "SUPER Bubble vibing in memory lanes... 🎶"},
        {"SUPER BUBBLE is sniffing your disk... 👃", "SUPER Bubble mapping disk galaxies... 🌌", "SUPER Bubble skateboarding across platters... 🛹"},
        {"SUPER BUBBLE is licking kernel strings... 👅", "SUPER Bubble massaging the kernel... 💆", "SUPER Bubble vibing with syscalls... 🎧"},
        {"SUPER BUBBLE is eating on your distro... 🍵", "SUPER Bubble sipping distro tea... ☕", "SUPER Bubble hacking into package stash... 🗃️"},
        {"SUPER BUBBLE is yapping at your GPU... 🎨", "SUPER Bubble drawing ASCII art at light speed... 🖌️", "SUPER Bubble roasting pixels... 🔥"},
        {"SUPER BUBBLE is finishing the scan... 🏁", "SUPER Bubble polishing the report... 📝", "SUPER Bubble doing a victory dance... 💃"}
    };

    int percent = 0;
    auto progress_bar = [&](int step_end, const vector<string> &msgs){
        while(percent<step_end){
            percent++;
            cout << "\r[";
            for(int i=0;i<40;i++) cout << (i<percent*40/100 ? '#' : ' ');
            cout << "] " << percent << "%" << flush;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout << "  " << random_msg(msgs) << "\n";
    };

    string cpu_model="Unknown";
    unsigned int threads=1;
    uint64_t mem_total=0, mem_used=0, disk_total=0, disk_used=0;
    string kernel="Unknown", distro_name="Unknown", gpu="Unknown";
    char hostbuf[256]; hostbuf[0]='\0';

#if defined(_WIN32) || defined(_WIN64)
    SYSTEM_INFO sysinfo; GetSystemInfo(&sysinfo); threads=sysinfo.dwNumberOfProcessors;
    MEMORYSTATUSEX memstat; memstat.dwLength=sizeof(memstat); GlobalMemoryStatusEx(&memstat);
    mem_total=memstat.ullTotalPhys; mem_used=memstat.ullTotalPhys - memstat.ullAvailPhys;
    if(GetComputerNameA(hostbuf, (LPDWORD)(sizeof(hostbuf)))){}
    cpu_model="Intel/AMD CPU";
    kernel="Windows Kernel";
    gpu="Generic GPU";
#elif defined(__linux__)
    auto read_first_matching_line=[&](const string &path,const string &key,char delim=':')->string{
        ifstream f(path); string line; while(getline(f,line)) if(line.rfind(key,0)==0){
            auto pos=line.find(delim); if(pos!=string::npos) return trim(line.substr(pos+1)); return trim(line);
        } return "";
    };

    cpu_model = read_first_matching_line("/proc/cpuinfo", "model name");
    if(cpu_model.empty()) cpu_model = read_first_matching_line("/proc/cpuinfo", "Hardware");
    threads = thread::hardware_concurrency();

    string mem_total_str = read_first_matching_line("/proc/meminfo", "MemTotal");
    string mem_avail_str = read_first_matching_line("/proc/meminfo", "MemAvailable");
    auto parse_kib = [](const string &s)->uint64_t { string num; for(char c:s) if(isdigit(c)) num.push_back(c); if(num.empty()) return 0; return stoull(num)*1024ULL; };
    mem_total = parse_kib(mem_total_str); mem_used = mem_total - parse_kib(mem_avail_str);

    struct statvfs vfs; if(statvfs("/", &vfs)==0){disk_total=uint64_t(vfs.f_frsize)*vfs.f_blocks; disk_used=disk_total-uint64_t(vfs.f_frsize)*vfs.f_bfree;}
    struct utsname uts; if(uname(&uts)==0) kernel=string(uts.sysname)+" "+string(uts.release); gethostname(hostbuf,sizeof(hostbuf));

    ifstream osf("/etc/os-release"); string line; while(getline(osf,line)){ if(line.rfind("PRETTY_NAME",0)==0){ distro_name=line.substr(line.find('=')+1); distro_name.erase(remove(distro_name.begin(),distro_name.end(),'"'),distro_name.end()); break; } }

    gpu=run_command("/usr/bin/lspci 2>/dev/null | grep -iE 'vga|3d|display' | head -n 1 | cut -d ':' -f3-");
#endif

    progress_bar(15, stage_msgs[0]);
    progress_bar(30, stage_msgs[1]);
    progress_bar(45, stage_msgs[2]);
    progress_bar(60, stage_msgs[3]);
    progress_bar(75, stage_msgs[4]);
    progress_bar(90, stage_msgs[5]);
    progress_bar(100, stage_msgs[6]);

    cout << MAGENTA << BLINK << "************ SUPER BUBBLE REPORT ************\n" << RESET;
    display_status("Host", hostbuf[0]?hostbuf:"(unknown)");
    display_status("Platform", platform);
    display_status("Distro", distro_name);
    display_status("Kernel", kernel);
    display_status("CPU", cpu_model);
    display_status("Threads", to_string(threads));
    display_status("Memory Used/Total", human_bytes(mem_used)+" / "+human_bytes(mem_total));
    display_status("Disk Used/Total", human_bytes(disk_used)+" / "+human_bytes(disk_total));
    display_status("GPU", gpu);
    cout << MAGENTA << "****************************************\n" << RESET;

    int score=0; if(threads>=4)score+=20; if(mem_total>=4ULL*1024*1024*1024)score+=30; if(disk_total>=100ULL*1024*1024*1024)score+=20; if(!gpu.empty())score+=30;
    string verdict,color;
    if(score<40){verdict="kinda crusty... 🪦"; color=RED;}
    else if(score<70){verdict="decent! 👍"; color=YELLOW;}
    else{verdict="a beast! 🐉🔥"; color=GREEN;}

    cout << BOLD << "Super Bubble Performance Meter: " << color << score << "/100" << RESET << "\n";
    cout << color << "Verdict: Super Bubble says your rig is " << verdict << RESET << "\n";

    cout << BLUE << "[STATUS] All super bubbles accounted for. Scan complete. Let the bubbles reign! ✨🫧🎉\n" << RESET;

    return 0;
}
