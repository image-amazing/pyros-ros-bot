#pragma once

#include <cstdio>
#include <cstring>

//#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace cv;
using namespace std;

#define DRAW_RICH_KEYPOINTS_MODE     1
#define DRAW_OUTLIERS_MODE           1

class objectDetector
{

enum { NONE_FILTER = 0, CROSS_CHECK_FILTER = 1 };

	public:

	objectDetector();

    // Set the Image Template
	void setImageTemplate(Mat img_t);

    // Manually specify the Image Template
    void setImageTemplate(vector<cv::KeyPoint> keypts, cv::Mat desc)
    {
        img_search_keypoints = keypts;
        img_template_descriptors = desc;
    }

    // Get the resulting Image Template's Keypoints
    vector<cv::KeyPoint> getImageTemplateKeypoints()
    {
        if (bSetImageTemplate) {
            return img_template_keypoints;
        }
        else {
            vector<cv::KeyPoint> empty;
            return empty;
        }
    }

    // Get the resulting Image Template's Descriptors
    cv::Mat getImageTemplateDescriptors()
    {
        if (bSetImageTemplate) {
            return img_template_descriptors;
        }
        else {
            cv::Mat empty;
            return empty;
        }
    }

	void setImageSearch(Mat img_s);

    void setImageSearch(vector<cv::KeyPoint> keypts, cv::Mat desc)
    {
        img_search_keypoints = keypts;
        img_search_descriptors = desc;
    }

	vector<cv::KeyPoint> getImageSearchKeypoints()
    {
        if (bSetImageSearch) {
            return img_search_keypoints;
        }
        else {
            vector<cv::KeyPoint> empty;
            return empty;
        }
    }

    cv::Mat getImageSearchDescriptors()
    {
        if (bSetImageSearch) {
            return img_search_descriptors;
        }
        else {
            cv::Mat empty;
            return empty;
        }
    }

    cv::Ptr<cv::DescriptorMatcher> getMatcher()
    {
        return descriptorMatcher;
    }

	void simpleMatching( cv::Ptr<cv::DescriptorMatcher>& descriptorMatcher,
						const cv::Mat& descriptors1, const cv::Mat& descriptors2,
						vector<cv::DMatch>& matches12 );
	void crossCheckMatching( cv::Ptr<cv::DescriptorMatcher>& descriptorMatcher,
							const cv::Mat& descriptors1, const cv::Mat& descriptors2,
							vector<cv::DMatch>& filteredMatches12, int knn=1 );

	void update();
	void doIteration( const cv::Mat& img1, Mat& img2,
					 vector<cv::KeyPoint>& keypoints1, const cv::Mat& descriptors1,
					 cv::Ptr<cv::FeatureDetector>& detector, cv::Ptr<cv::DescriptorExtractor>& descriptorExtractor,
					 cv::Ptr<cv::DescriptorMatcher>& descriptorMatcher, int matcherFilter,
					 double ransacReprojThreshold);


	vector<cv::Point2f> img_search_points_inliers[2], img_search_points_outliers[2];
	vector<cv::Point2f> img_template_boundingbox;
	cv::Point2f src_corners[4], dst_corners[4], prev_dst_corners[4];

private:

	int matcherFilterType;

	bool bSetImageTemplate, bSetImageSearch;

	cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> descriptorExtractor;
    cv::Ptr<cv::DescriptorMatcher> descriptorMatcher;

	cv::Mat img_template, img_search;

	bool bInitialized, bTracking;
	cv::Mat prev_img_search;

	vector<cv::KeyPoint> img_search_keypoints, img_template_keypoints;
	vector<cv::KeyPoint> img_search_keypoints_inliers[2], img_search_keypoints_outliers[2];

	cv::Mat img_search_descriptors, img_template_descriptors;

	vector<cv::DMatch> filteredMatches;

	float ransacReprojThreshold;


    cv::Mat H12;

	bool bShowImage;
    cv::Mat drawImg;
	string winName;

};