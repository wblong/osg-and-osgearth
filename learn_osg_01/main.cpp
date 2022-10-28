#include <osgViewer/Viewer>
#include <iostream>
 
int main(int argc, char** argv)
{
	std::cout << "Hello, osg!" << std::endl;
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setUpViewInWindow(50, 50, 800, 600);
	return viewer->run();
}