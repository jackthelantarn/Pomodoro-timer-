#ifndef WEBSITEBLOCKER_H
#define WEBSITEBLOCKER_H

#include <string>
#include <set>

class WebsiteBlocker {
private:
    std::string hostsFilePath;
    std::set<std::string> blockedWebsites;

    bool isValidURL(const std::string& url);
    bool isAlreadyBlocked(const std::string& website);

public:
    WebsiteBlocker(const std::string& path = "C:\\Windows\\System32\\drivers\\etc\\hosts");

    void blockWebsite(const std::string& website);
    void unblockWebsite(const std::string& website);
    void listBlockedSites();
};

#endif // WEBSITEBLOCKER_H
