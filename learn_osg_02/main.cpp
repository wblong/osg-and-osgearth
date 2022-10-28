#include <iostream>
#include <string>
#include <filesystem>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

using namespace std;


static void findDir(const string& dir, vector<string>& subDirs)
{
    //
    subDirs.clear();

    for (auto& i : filesystem::directory_iterator(dir)) {
        if (i.path().string() == "." || i.path().string() == "..")
            continue;
        if (i.is_directory()) {
            subDirs.push_back(i.path().string());
        }
    }
}

static std::string DirOrPathGetName(std::string filePath)
{
    size_t m = filePath.find_last_of('\\');
    if (m == string::npos)
    {
        return filePath;
    }

    size_t p = filePath.find_last_of('.');
    if (p != string::npos && p > m)		
    {
        filePath.erase(p);
    }

    std::string dirPath = filePath;
    dirPath.erase(0, m + 1);
    return dirPath;
}

void createObliqueIndexes(std::string fileDir)
{
	string dataDir = fileDir + "/Data";

	osg::ref_ptr<osg::Group> group = new osg::Group();
	vector<string> subDirs;
	findDir(dataDir, subDirs);

	for (size_t i = 0; i < subDirs.size(); i++)
	{
		string name = DirOrPathGetName(subDirs[i]);
		string path = subDirs[i] + "/" + name + ".osgb";

		if (!filesystem::exists(path))
			continue;
		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(path);
		osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD();
		if (!node.valid())
			continue;
		//auto bs=node->computeBound();
		auto bs = node->getBound();
		auto c = bs.center();
		auto r = bs.radius();
		lod->setCenter(c);
		lod->setRadius(r);
		lod->setRangeMode(osg::LOD::RangeMode::PIXEL_SIZE_ON_SCREEN);
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->getOrCreateStateSet();
		lod->addChild(geode.get());

		std::string relativeFilePath = "./Data/" + name + "/" + name + ".osgb";

		lod->setFileName(0, "");
		lod->setFileName(1, relativeFilePath);

		lod->setRange(0, 0, 1.0);																							//第一层不可见
		lod->setRange(1, 1.0, FLT_MAX);

		lod->setDatabasePath("");

		group->addChild(lod);
	}
	std::string outputLodFile = fileDir + "/Data.osgb";
	osgDB::writeNodeFile(*group, outputLodFile);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;
	if (!filesystem::exists(argv[1]))
		return -1;
	std::string fileDir = argv[1];
    std::string outputLodFile = fileDir + "/Data.osgb";
	createObliqueIndexes(fileDir);

	osgViewer::Viewer viewer;
	osg::Node * node = new osg::Node;
	node = osgDB::readNodeFile(outputLodFile);
	viewer.setSceneData(node);
	viewer.setUpViewInWindow(50, 50, 800, 600);
	return viewer.run();
}
