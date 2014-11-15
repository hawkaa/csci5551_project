#include <iostream>
#include <math.h>
#include <vector>



	class Point {
		double xcord, ycord;
	public:
		void set_values (double, double);
		double getx();
		double gety();
	};
	
	class LineSegment{
		Point *beginning,*end;
	public:
		void DefineLineSegment(Point*, Point*);
		double getlength(void);
		Point getcenter(void);
		Point* getstart();
		Point* getend();
	};

	
	Point* LineSegment::getstart(){
		return beginning;
	}

	Point* LineSegment::getend(){
		return end;
	}
	
	void LineSegment::DefineLineSegment(Point *firstpoint, Point *secondpoint){
		beginning = firstpoint;
		end = secondpoint;
	}
	
	
	double LineSegment::getlength(){
		return sqrt(pow(end->getx()-beginning->getx(),2)+pow(end->gety()-beginning->gety(),2));
	}

	Point LineSegment::getcenter(){
		double midx = (beginning->getx() + end->getx()) / 2;
		double midy = (beginning->gety() + end->gety()) / 2;
		Point intermediatemid;
		intermediatemid.set_values(midx, midy);
		return intermediatemid;
	}
	
	void Point::set_values(double x, double y){
		xcord = x;
		ycord = y;
	}

	double Point::getx(){
		return xcord;
	}

	double Point::gety(){
		return ycord;
	}

	int main()
	{
		std::vector<double> Inputx;
		std::vector<double> Inputy;
		std::vector<Point> Points;
		std::vector<LineSegment> LineSegments;
		std::vector<LineSegment> PotentialCandidates;

		//create test input
		for (double samples = 0; samples < 360; samples++){
			/*
			if (samples < 25){
				Inputx.push_back(samples);
				Inputy.push_back(100);
			}

			if (24 < samples && samples < 51){
				Inputx.push_back(samples);
				Inputy.push_back(200);
			}

			if (50 < samples){
				Inputx.push_back(samples);
				Inputy.push_back(100);
			}
			*/
			
			if (samples < 100){
				Inputx.push_back(samples);
				Inputy.push_back(samples * 2);
			}
			if (99< samples && samples< 151){
				Inputx.push_back(samples);
				Inputy.push_back(samples * 5);
			}
			
			if (150< samples && samples< 201){
				Inputx.push_back(samples);
				Inputy.push_back(200);
			}
			
			if (samples == 162){
				Inputx.push_back(samples);
				Inputy.push_back(550);
			}
			
			if (163< samples && samples< 201){
				Inputx.push_back(samples);
				Inputy.push_back(200);
			}
			
			if (200< samples && samples< 226){
				Inputx.push_back(samples);
				Inputy.push_back(500);
			}
			if (225< samples && samples< 276){
				Inputx.push_back(samples);
				Inputy.push_back(200);
			}
			if (275< samples && samples< 327){
			Inputx.push_back(samples);
			Inputy.push_back(-5*samples+2130);
			}
			if (326< samples && samples< 360){
				Inputx.push_back(samples);
				Inputy.push_back(-2*samples+1154);
			}
			


			//display the input
			//std::cout << Inputx[samples] << ", " <<Inputy[samples] <<std::endl;
		}

		//create point object vector with input points
		for (double samples = 0; samples < Inputx.size(); samples++){
			Point intermediatepoint;
			intermediatepoint.set_values(Inputx[samples], Inputy[samples]);
			Points.push_back(intermediatepoint);
		}

		//display values of each point in Points vector
		/*
		for (double pointsample = 0; pointsample < Points.size(); pointsample++){
			std::cout << Points[pointsample].getx() << ", " << Points[pointsample].gety() << std::endl;
		}
		*/


		//define initial starting vector location for distance analysis
		double startpoint = 0;

		//calculate distances between points and detirmine if line segment
		for (double endpoint = 1; endpoint < Points.size(); endpoint++){
			LineSegment intermediatesegment;
			intermediatesegment.DefineLineSegment(&Points[endpoint-1], &Points[endpoint]);

			//define condition at which the distance between consecutive points is large
			//enough to be considered a seperate line
			if (intermediatesegment.getlength() > 3){
				LineSegment discoveredsegment;
				LineSegment Savedsegment;
				discoveredsegment.DefineLineSegment(&Points[startpoint], &Points[endpoint - 1]);
				Savedsegment = discoveredsegment;
			//	if (discoveredsegment.)
				//test to see if discovered line segment consists of consecutive points, if so do not add to linesegment vector
				if ((endpoint - 1) - startpoint > 1){
					std::cout << "start" << Points[startpoint].getx() << ", " << Points[startpoint].gety() << std::endl;
					std::cout << "end" << Points[endpoint - 1].getx() << ", " << Points[endpoint - 1].gety() << std::endl;
					LineSegments.push_back(discoveredsegment);
				}
				startpoint = endpoint;
			}


			//add in condition for when the loop reaches the end of the Points vector to conclude last line segment
			if (endpoint == Points.size() - 1){
				LineSegment finalsegment;
				finalsegment.DefineLineSegment(&Points[startpoint], &Points[endpoint]);
				//test to see if discovered line segment consists of consecutive points, if so do not add to linesegment vector
				if (endpoint-startpoint > 1){
					std::cout << "start" << Points[startpoint].getx() << ", " << Points[startpoint].gety() << std::endl;
					std::cout << "end" << Points[endpoint - 1].getx() << ", " << Points[endpoint - 1].gety() << std::endl;
					LineSegments.push_back(finalsegment);
				}
			}
		}

		//display values of length and Center
		
		for (double linesample = 0; linesample < LineSegments.size(); linesample++){
			std::cout << "Length= " << LineSegments[linesample].getlength() << " Center="<<LineSegments[linesample].getcenter().getx() << ", " << LineSegments[linesample].getcenter().gety()<<std::endl;
		}

		std::cout << std::endl;
		
		//test to see if the center of two line segments is within desired seperation
		for (double firstlinesegment = 0; firstlinesegment < LineSegments.size()-1; firstlinesegment++){
			for (double secondlinesegment = firstlinesegment+1; secondlinesegment < LineSegments.size(); secondlinesegment++){
				LineSegment segmentseperation;
				segmentseperation.DefineLineSegment(&LineSegments[firstlinesegment].getcenter(), &LineSegments[secondlinesegment].getcenter());
				if (10<segmentseperation.getlength() && segmentseperation.getlength()<10){
					PotentialCandidates.push_back(segmentseperation);
					//display information on potential linesegments for leg detection
				//	std::cout << "Length= " << segmentseperation.getlength() << " Center=" << segmentseperation.getcenter().getx() << ", " << segmentseperation.getcenter().gety() << std::endl;
				}
			}
		}	
		std::cout << std::endl;
		//std::cout << "Length= 37.5 Center=231.25, 350";
}

