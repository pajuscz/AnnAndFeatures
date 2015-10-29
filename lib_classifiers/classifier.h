#ifndef CLASSIFIER_H
#define CLASSIFIER_H

// OpenCV headers
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>

// Standard library header files
#include <iostream>
#include <string>
#include <vector>

#include "lib_support/support.h"

using namespace std;
using namespace cv;



class Classifier {

public:
    static const string C_ANN, C_SVM;
    Classifier();
    virtual ~Classifier() = 0;
    virtual string name() = 0;

    // Virtual functions implemented in a child class
    virtual void train(cv::Mat_<float> &trainData, std::vector<uchar> &labels) = 0;
    virtual std::vector<uchar> predict(cv::Mat_<float> &testData) = 0;
    virtual uchar predictResponse(cv::Mat_<float> &testData) = 0;

    virtual int loadFromParams(string params) = 0;
    virtual string getStrSettings() = 0;

    virtual int loadFromFile(const char * filename) = 0;
    virtual int save2file(const char * filename) = 0;

    void evaluate(std::vector<uchar> predictedLabels, std::vector<uchar> trueLabels, int numClasses);
    double evaluateVerbose(std::vector<uchar> predictedLabels, std::vector<uchar> trueLabels);
    static cv::Mat cr8ResponseMat(std::vector<uchar> & labels, int numberOfSamples);
    // Classifier methods
    /**
     * @brief Set string values for labels
     * @param labels Array of string with labels
     * @param numOfClasses number of labels
     */
    void setLabels( string labels[],int numOfClasses);

    void setLabels(vector<string> vec_labels);
    /**
     * @brief Get index of given string label
     * @param label string of a label
     * @return index(numerical label) of the string, returns numberOfClasses+1 if doesn't exist
     */
    int getLabelIndex(string label);
    /**
     * @brief Get string value of numerical label
     * @param iLabel index(numerical value) of a label
     * @return string value of label given by its index(numerical label), "null" if doesn't exist
     */
    string getLabelString(uint iLabel);
    /**
     * @brief Extracts labels from filenames (or with path) into ANN object. Requires strLabel to be as name of the image
     * Attention! If it will mar as a label if strLabel occurs in the path (any folder or filename)
     * Therefore if you want to label images by separating them in different directories or by filename
     * both is possible but don't mix them
     * @param fileNames vector of strings with filenames
     * @return vector with uchar labels
     */
    vector<uchar> extLabelFromFileName(vector<string> &fileNames);
    /**
     * @brief Checks label extraction result
     * @return True if there was an error in LabelExtraction (extra image/extra label)
     */
    bool hasNullLabel();
    /**
     * @brief findStrLabel
     * @param filename
     * @return uchar ID of the class given by string label name
     */
    uchar findStrLabel(const string & filename);

    void setFeatureVectorSize(int attributesPerSample);

    string getStrLabels();

    int numberOfClasses;
    int attributesPerSample;

    void printLabels(vector<string> filename, vector<uchar> labels);
private:
    bool isRestMember;
    std::vector<string> strLabels;


    bool nullLabel;
};


#endif // CLASSIFIER_H
