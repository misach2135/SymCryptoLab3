#include "ciphrator.hpp"

std::string ciphrator::encrypt(const std::string& text, int32_t a, int32_t b)
{
    std::string res;
    int32_t m2 = utils::M * utils::M;
    for (int i = 0; i < text.size(); i += 2)
    {
        std::string bigram = text.substr(i, 2);
        int32_t bigramNum = utils::bigramToNum(bigram);
        bigramNum = utils::mod(a * bigramNum + b, m2);
        bigram = utils::numToBigram(bigramNum);
        res += bigram;
    }
    return res;
}

std::string ciphrator::decrypt(const std::string& text, int32_t a, int32_t b)
{
    std::string res;
    int32_t m2 = utils::M * utils::M;
    for (int i = 0; i < text.size(); i += 2)
    {
        std::string bigram = text.substr(i, 2);
        int32_t bigramNum = utils::bigramToNum(bigram);
        int32_t aInverse = utils::getInversed(a, m2);
        bigramNum = utils::mod(aInverse * (bigramNum - b), m2);
        bigram = utils::numToBigram(bigramNum);
        res += bigram;
    }
    return res;
}


/// <summary>
/// Hack cipher)
/// </summary>
/// <param name="text">Encrypted text to decrypt</param>
/// <param name="naturalBigrams">Array of natural bigrams which sorted in descending order(firstly, most often)</param>
/// <returns>Decrypted text</returns>
std::string ciphrator::hack(const std::string& text, std::vector<std::string> naturalBigrams)
{
    return std::string();
}
