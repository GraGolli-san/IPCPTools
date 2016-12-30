#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


int main(int argc, char** argv)
{
    IplImage *frame = 0;
    CvCapture* capture = 0;
    int frameCounter = 0;
    int c;
    CvVideoWriter* aviWriter = 0;

    printf("Capture from camera\n");
    capture = cvCaptureFromCAM(0);

    if (!capture)
    {
        printf("Can not initialize video capturing\n\n");
        return -1;
    }

    for (;;)
    {
        frame = cvQueryFrame(capture);
        if (!frame)
            break;

        //First time:
        if (frameCounter == 0 && frame)
        {
            cvNamedWindow("Recorder", 1);
        }

        // If we've got an rawImage and are good to go:                
        if (frame)
        {
            //Display
            cvShowImage("Recorder", frame);
        }

        /* Save fg to avi file: */
        if (aviWriter == NULL)
        {
            CvSize	imgSize = cvSize(frame->width, frame->height);
            aviWriter = cvCreateVideoWriter(
                "hoge.avi",
                CV_FOURCC('D', 'I', 'B', ' '),
                30,
                imgSize);
        }
        cvWriteFrame(aviWriter, frame);

        // User input:
        c = cvWaitKey(10) & 0xFF;
        c = tolower(c);
        // End processing on ESC, q or Q
        if (c == 27 || c == 'q')
            break;

        frameCounter++;
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow("Recorder");
    if (aviWriter)cvReleaseVideoWriter(&aviWriter);

    return 0;
}

