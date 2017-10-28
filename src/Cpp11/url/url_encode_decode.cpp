//I copied url_encode from https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
std::string url_encode(const std::string &value)
{
    using namespace std;
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (auto i = value.begin(), n = value.end(); i != n; ++i) {
        auto c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

std::string url_decode(const std::string &value)
{    
    std::string ret;    
    for (unsigned i = 0; i < value.length();)
    {
        if (value[i] == '%')
        {            
            std::string hex_str{value[i + 1], value[i + 2]};
            std::stringstream escaped;
            escaped  << std::hex << hex_str;
            int ch;
            escaped >> std::hex >> ch;
            ret.push_back(static_cast<char>(ch));
            i += 3;
        }
        else
        {
            ret.push_back(value[i]);
            ++i;
        }
    }
    return ret;
}