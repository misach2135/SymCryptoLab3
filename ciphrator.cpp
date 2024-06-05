#include "ciphrator.hpp"

// Дуже примітивний розпізнавач. Настільки, що я боюсь, що він все ламатиметиме)
bool ciphrator::isNaturalLang(const std::string& text, double epsilon)
{
    auto textInfo = utils::TextInfoFromStringWithoutSpaces(text);

    bool entropyCheck = abs(textInfo.symbolsEntropy - ciphrator::H1Entropy) < epsilon;
    bool entropyH2Check = abs(textInfo.overlappingBigramsEntropy - ciphrator::H2OverlappingEntropy) < epsilon;

    if (entropyCheck && entropyH2Check) return true;
    
    return false;

}

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
void ciphrator::hack(const std::string& text, std::vector<std::string> naturalBigrams, std::ofstream& out)
{
    auto textInfo = utils::TextInfoFromStringWithoutSpaces(text);
    auto mostFrequentBigrams = utils::getMostFrequentBigrams(textInfo.nonOverlappingBigramsCount, naturalBigrams.size());
    auto m2 = utils::M * utils::M;

    for (int i1 = 0; i1 < mostFrequentBigrams.size(); i1++)
    {
        auto Y1 = utils::bigramToNum(mostFrequentBigrams[i1].first);
        
        for (int i2 = 0; i2 < mostFrequentBigrams.size(); i2++)
        {
            if (i1 == i2) continue;
            auto Y2 = utils::bigramToNum(mostFrequentBigrams[i2].first);

            int32_t Y1Y2 = utils::mod(Y1 - Y2, m2);

            for (int j1 = 0; j1 < naturalBigrams.size(); j1++)
            {
                auto X1 = utils::bigramToNum(naturalBigrams[j1]);

                for (int j2 = 0; j2 < naturalBigrams.size(); j2++)
                {
                    if (j1 == j2) continue;
                    auto X2 = utils::bigramToNum(naturalBigrams[j2]);
                    int32_t X1X2 = utils::mod(X1 - X2, m2);

                    std::list<int64_t> aList = utils::solveEquation(X1X2, Y1Y2, m2);
                    if (aList.empty()) continue;

                    for (const auto& a : aList)
                    {
                        int32_t b = utils::mod(Y1 - a * X1, m2);

                        std::string decrypted = decrypt(text, a, b);

                        if (isNaturalLang(decrypted, 0.3))
                        {
                            out << "Keys a = " << a << ", b = " << b << ": \n";
                            out << decrypted << "\n\n";
                        }
                    }
                }
            }

        }
        
    }
   
}
