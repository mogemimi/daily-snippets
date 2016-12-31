// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "spellcheck.h"
#import <AppKit/AppKit.h>
#include <utility>

namespace somera {

std::string NativeSpellChecker::correctSpelling(const std::string& word)
{
    NativeSpellCheckOptions options;
    options.language = "en_US";
    return correctSpelling(word, options);
}

std::string NativeSpellChecker::correctSpelling(
    const std::string& word,
    const NativeSpellCheckOptions& options)
{
    if (word.empty()) {
        return "";
    }

    NSSpellChecker* checker = [NSSpellChecker sharedSpellChecker];
    NSString* string = [NSString stringWithUTF8String:word.c_str()];
    NSString* language = [NSString stringWithUTF8String:options.language.c_str()];

    NSString* correction = [checker correctionForWordRange:NSMakeRange(0, [string length])
        inString:string
        language:language
        inSpellDocumentWithTag:0];

    if (correction != nil) {
        return [correction UTF8String];
    }
    return "";
}

std::vector<std::string> NativeSpellChecker::findClosestWords(const std::string& word)
{
    NativeSpellCheckOptions options;
    options.language = "en_US";
    return findClosestWords(word, options);
}

std::vector<std::string> NativeSpellChecker::findClosestWords(
    const std::string& word,
    const NativeSpellCheckOptions& options)
{
    if (word.empty()) {
        return {};
    }

    NSSpellChecker* checker = [NSSpellChecker sharedSpellChecker];
    NSString* string = [NSString stringWithUTF8String:word.c_str()];
    NSString* language = [NSString stringWithUTF8String:options.language.c_str()];

    NSArray<NSString*>* corrections = [checker
        guessesForWordRange:NSMakeRange(0, [string length])
        inString:string
        language:language
        inSpellDocumentWithTag:0];

    std::vector<std::string> results;
    if (corrections.count > 0) {
        results.reserve(corrections.count);
    }
    for (NSString* correction in corrections) {
        results.push_back([correction UTF8String]);
    }
    return results;
}

class SpellCheckerMac final : public SpellChecker {
public:
    SpellCheckResult Suggest(const std::string& word)
    {
        SpellCheckResult result;
        result.correctlySpelled = false;
        result.suggestions = NativeSpellChecker::findClosestWords(word);
        if (result.suggestions.empty()) {
            result.correctlySpelled = true;
        }
        return result;
    }
    
    void AddWord(const std::string& word)
    {
    }
    
    void RemoveWord(const std::string& word)
    {
    }
};

std::shared_ptr<SpellChecker> CreateSpellCheckerMac()
{
    return std::make_shared<SpellCheckerMac>();
}

} // namespace somera
