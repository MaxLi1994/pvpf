//
// Created by Jiabei on 2018/7/24.
//
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE TaskExecutionScheduler
#endif
#include <boost/test/unit_test.hpp>
#include <pvpf/task_execution/scheduler.hpp>
#include <rapidjson/document.h>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <pvpf/config/config_reader.hpp>

BOOST_AUTO_TEST_SUITE(scheduler_executable)
using namespace std;
using namespace pvpf;
using namespace rapidjson;
Document load_json_conf(const string &file)
{
    boost::filesystem::path filePath(file);
    Document d;

    if (!boost::filesystem::exists(filePath))
    {
        cerr << "Configuration file not found" << endl;
        return d;
    }
    else if (boost::filesystem::is_regular_file(filePath))
    {
        string extension = filePath.extension().string();
        if (extension != ".json")
        {
            cerr << "Path shoud be a json file" << endl;
            return d;
        }
    }
    else
    {
        cerr << "Path should be a json file" << endl;
        return d;
    }

    boost::filesystem::ifstream inFile;
    inFile.open(filePath); //open the input file

    stringstream strStream;
    strStream << inFile.rdbuf();  //read the file
    string str = strStream.str(); //str holds the content of the file

    char char_array[str.size() + 1];
    strcpy(char_array, str.c_str());

    d.Parse(char_array);

    return d;
}

BOOST_AUTO_TEST_SUITE_END()