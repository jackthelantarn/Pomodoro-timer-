#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> // for remove(), rename()

class WebsiteBlocker {
private:
    std::string hostsFilePath;
    std::vector<std::string> blockedWebsites;

    bool isValidURL(const std::string& url) {
        // Basic validation: contains a dot, no spaces
        return url.find('.') != std::string::npos && url.find(' ') == std::string::npos;
    }

    bool isAlreadyBlocked(const std::string& website) {
        std::ifstream file(hostsFilePath.c_str());
        if (!file.is_open()) {
            std::cerr << "Cannot open hosts file for checking.\n";
            return false;
        }

        std::string line;
        std::string entry = "127.0.0.1 " + website;
        while (std::getline(file, line)) {
            if (line == entry) return true;
        }
        return false;
    }

public:
    WebsiteBlocker(const std::string& path = "C:\\Windows\\System32\\drivers\\etc\\hosts")
        : hostsFilePath(path) {}

    void blockWebsite(const std::string& website) {
        if (!isValidURL(website)) {
            std::cout << "Invalid website URL format.\n";
            return;
        }

        if (isAlreadyBlocked(website)) {
            std::cout << "Website already blocked.\n";
            return;
        }

        std::ofstream file(hostsFilePath.c_str(), std::ios::app);
        if (file.is_open()) {
            file << "127.0.0.1 " << website << "\n";
            blockedWebsites.push_back(website);
            std::cout << "Blocked: " << website << "\n";
        } else {
            std::cerr << "Failed to open hosts file. Run as administrator.\n";
        }
    }

    void unblockWebsite(const std::string& website) {
        std::ifstream inFile(hostsFilePath.c_str());
        std::ofstream outFile("temp_hosts.txt");

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "Failed to open file(s) for unblocking.\n";
            return;
        }

        std::string line;
        std::string blockEntry = "127.0.0.1 " + website;
        bool found = false;

        while (std::getline(inFile, line)) {
            if (line != blockEntry) {
                outFile << line << "\n";
            } else {
                found = true;
            }
        }

        inFile.close();
        outFile.close();

        if (found) {
            std::remove(hostsFilePath.c_str());
            std::rename("temp_hosts.txt", hostsFilePath.c_str());

            // Remove from blocked list
            for (size_t i = 0; i < blockedWebsites.size(); ++i) {
                if (blockedWebsites[i] == website) {
                    blockedWebsites.erase(blockedWebsites.begin() + i);
                    break;
                }
            }

            std::cout << "Unblocked: " << website << "\n";
        } else {
            std::cout << "Website not found in blocked list.\n";
            std::remove("temp_hosts.txt");
        }
    }

    void listBlockedSites() {
        std::cout << "Currently blocked sites:\n";
        for (size_t i = 0; i < blockedWebsites.size(); ++i) {
            std::cout << "- " << blockedWebsites[i] << "\n";
        }
    }
};

int main() {
    WebsiteBlocker blocker;
    std::string command, website;

    std::cout << "Website Blocker - C++98 Compatible Version\n";

    while (true) {
        std::cout << "\nEnter command (block / unblock / list / exit): ";
        std::cin >> command;

        if (command == "block") {
            std::cout << "Enter website to block (e.g., youtube.com): ";
            std::cin >> website;
            blocker.blockWebsite(website);
        } else if (command == "unblock") {
            std::cout << "Enter website to unblock: ";
            std::cin >> website;
            blocker.unblockWebsite(website);
        } else if (command == "list") {
            blocker.listBlockedSites();
        } else if (command == "exit") {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Unknown command. Try again.\n";
        }
    }

    return 0;
}
