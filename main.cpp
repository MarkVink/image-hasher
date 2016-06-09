#include <iostream>
#include "CImg/CImg.h"
#include "pHash/pHash.h"
#include "cxxopts/cxxopts.hpp"
using namespace std;

void fileToDigest(Digest &dig, const char *file)
{
    try {
        ph_image_digest(file, 1.0, 1.0, dig, 180);
    } catch (CImgException) {
        cout << "Error(" << errno << ") The passed image " << file << " does not exists" << endl;
        exit(EXIT_FAILURE);
    }
}

void calculateSimilarity(map<string, double> &images, const string &dir, const string &file)
{
    Digest dig_original;
    fileToDigest(dig_original, file.c_str());

    DIR *dp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening dir" << endl;
        exit(EXIT_FAILURE);
    }

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (strlen(dirp->d_name) >= 4 && strcmp(dirp->d_name + strlen(dirp->d_name) - 4, ".jpg") == 0) {
            const char *filename = (string() + dir + '/' + dirp->d_name).c_str();

            Digest dig_file;
            fileToDigest(dig_file, filename);

            double pcc;
            ph_crosscorr(dig_original, dig_file, pcc, 0.90);

            images.insert({dirp->d_name, pcc});
        }
    }
}

void removeBelowThreshold(map<string, double> &images, const double &threshold)
{
    map<string, double>::iterator iter = images.begin();

    while (iter != images.end()) {
        if (iter->second < threshold) {
            iter = images.erase(iter);
        } else {
            ++iter;
        }
    }
}

void printImageKeys(map<string, double> &images)
{
    stringstream ss;
    for (auto iter = images.begin(); iter != images.end(); ++iter) {
        ss << iter->first << " ";
    }

    string output = ss.str();

    cout << output.substr(0, output.size()-1) << endl;
}

int main(int argc, char **argv)
{
    try
    {
        cxxopts::Options options(argv[0], "Find similar images in directory");
        options.add_options()
                ("d,dir", "Directory", cxxopts::value<string>()->default_value("profiles"), "")
                ("f,file", "File", cxxopts::value<string>(), "")
                ("t,threshold", "Threshold", cxxopts::value<string>()->default_value("0.85"), "");

        options.parse_positional("file");
        options.parse(argc, argv);

        if (!options.count("file"))
        {
            cout << "Pass an file for comparison" << endl;
            exit(EXIT_FAILURE);
        }

        string dir = options["dir"].as<string>();
        string file = options["file"].as<string>();

        map <string, double> images;
        calculateSimilarity(images, dir, file);

        double threshold = atof(options["threshold"].as<string>().c_str());
        removeBelowThreshold(images, threshold);
        printImageKeys(images);

    } catch (const cxxopts::OptionException& e)
    {
        cout << "error parsing options: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}