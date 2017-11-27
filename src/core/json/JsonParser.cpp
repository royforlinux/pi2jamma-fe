#include "core/json/JsonParser.hpp"
#include "core/json/Parser.hpp"
#include "file/File.hpp"

Result JsonLoadFromFile( Json& json, const char* pFilename )
{
    File file;
    Result r = file.open(pFilename, File::OpenMode::Read);
    if(r.peekFailed()) {
        return r;
    }

    FileSize fileSize = 0;
    r = file.getSize(fileSize);
    if(r.peekFailed()) {
        return r;
    }

    std::vector<char> s;
    s.resize(fileSize);

    r = file.readExactly(s.data(), s.size());
    if (r.peekFailed()) {
        return r;
    }

    LogFmt("starting parse..%d\n", (int)fileSize);

    StringParserAssembly stringParser(s.data(), s.size());
    JsonParser<StringParserAssembly::ParserType> jsonParser(stringParser.GetParser());

    bool result = jsonParser.Parse(&json);
    if (!result) {
        return
            Result::makeFailureWithString(
                formatString(
                    "JSON ERROR: %s Line: %d\n",
                    jsonParser.GetError().c_str(),
                    (int) stringParser.GetParser()->GetLineCount()));                 

    }
    
    return Result::makeSuccess();
};
