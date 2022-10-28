#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
 
#include <iostream>
 
int main(int argc, char** argv)
{
	std::cout << "Hello, osg!" << std::endl;
 
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setUpViewInWindow(50, 50, 800, 600);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 1.0f)));
	osg::ref_ptr<osg::Texture> texture = new osg::Texture2D(osgDB::readRefImageFile("E:/code/osgDemo/data/world.png"));
	auto stateSet = geode->getOrCreateStateSet();
	stateSet->setTextureAttributeAndModes(0, texture);
	viewer->setSceneData(geode);
	return viewer->run();
}