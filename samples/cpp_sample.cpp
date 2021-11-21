#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

struct tinydir_dir;

class TinyDir {
public:
    TinyDir(const std::string& path);
    ~TinyDir();
    std::string baseName() const;
    std::list<std::string> listDir();

private:
    tinydir_dir* dir;
};

#include <tinydir.h>

TinyDir::TinyDir(const std::string& path) : dir(new tinydir_dir) {
    if (tinydir_open(dir, path.c_str()) == -1) {
        throw std::invalid_argument{"path"};
    }
}

TinyDir::~TinyDir() {
    tinydir_close(dir);
    delete dir;
}

std::string TinyDir::baseName() const {
    const std::string path{dir->path};
    auto lastSlash = path.find_last_of("/\\");
    if (lastSlash == std::string::npos) {
        return path;
    }
    return path.substr(lastSlash + 1);
}

std::list<std::string> TinyDir::listDir()
{
    std::list<std::string> files;

    while (dir->has_next)
    {
        tinydir_file file;                                
        tinydir_readfile(dir, &file);

        files.push_back(std::string{dir->path} + "/" + file.name);

        tinydir_next(dir);
    }

    return files;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: cpp_sample filename\n";
        return 1;
    }
    TinyDir td{argv[1]};
    std::cout << "Basename is " << td.baseName() << "\n";
    return 0;
}

