#include "WebsiteBlocker.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // for remove(), rename()

WebsiteBlocker::WebsiteBlocker(const std::string& path)
    : hostsFilePath(path) {
}

bool WebsiteBlocker::isValidURL(const std::string& url) {
    return url.find('.') != std::string::npos && url.find(' ') == std::string::npos;
}

bool WebsiteBlocker::isAlreadyBlocked(const std::string& website) {
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

void WebsiteBlocker::blockWebsite(const std::string& website) {
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
        blockedWebsites.insert(website);  
        std::cout << "Blocked: " << website << "\n";
		system("ipconfig /flushdns"); // Flush DNS cache to apply changes immediately

    }
    else {
        std::cerr << "Failed to open hosts file. Run as administrator.\n";
    }
}

void WebsiteBlocker::unblockWebsite(const std::string& website) {
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
        }
        else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        std::remove(hostsFilePath.c_str());
        std::rename("temp_hosts.txt", hostsFilePath.c_str());

        blockedWebsites.erase(website);  // ✅ direct erase from set
        std::cout << "Unblocked: " << website << "\n";
    }
    else {
        std::cout << "Website not found in blocked list.\n";
        std::remove("temp_hosts.txt");
    }
}

void WebsiteBlocker::listBlockedSites() {
    std::cout << "Currently blocked sites:\n";
    for (const auto& site : blockedWebsites) {
        std::cout << "- " << site << "\n";
    }
}
