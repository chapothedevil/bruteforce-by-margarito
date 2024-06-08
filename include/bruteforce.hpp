#ifndef BRUTEFORCE_HPP
#define BRUTEFORCE_HPP

#include <string>
#include <vector>

class BruteForce {
public:
    void loadPasswords(const std::string &filename);
    bool tryLogin(const std::string &url, const std::string &username, const std::string &password, const std::string &failureResponse);
    const std::vector<std::string>& getPasswords() const { return passwords; }

private:
    std::vector<std::string> passwords;
};

#endif // BRUTEFORCE_HPP
