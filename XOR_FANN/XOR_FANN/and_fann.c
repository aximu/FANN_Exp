

// #include <doublefann.h>
#include "../../FANN-2.2.0-Source/src/include/doublefann.h"
#pragma comment(lib, "../../FANN-2.2.0-Source/bin/fanndouble.lib")

//训练+神经网络
//c = a and b; 布尔变量与运算

/*训练*/
void train()
{
    const unsigned int NUM_INPUT = 2;
    const unsigned int NUM_OUTPUT = 1;
    const unsigned int NUM_LAYERS = 3;
    const unsigned int NUM_NEURONS_HIDDEN = 2;
    const float DESIRED_ERROR = (const float)0.0001;
    const unsigned int MAX_EPOCHS = 1000;
    const unsigned int EPOCHS_BETWEEN_REPORTS = 10;

    struct fann* ann;
    struct fann_train_data* data;

    // 样本训练
    ann = fann_create_standard(NUM_LAYERS, NUM_INPUT, NUM_NEURONS_HIDDEN, NUM_OUTPUT);
    data = fann_read_train_from_file("xor.fann");
    fann_set_activation_function_hidden(ann, FANN_LINEAR);
    fann_set_activation_function_output(ann, FANN_LINEAR);
    fann_train_on_data(ann, data, MAX_EPOCHS, EPOCHS_BETWEEN_REPORTS, DESIRED_ERROR);
    fann_save(ann, "xor.fann.net");
    printf("Testing network. %f\n", fann_test_data(ann, data));              //测试一组训练数据并计算训练数据的 MSE

    fann_destroy(ann);

}

/*执行测试*/
void exec(fann_type a, fann_type b)
{
    struct fann* ann;

    fann_type* calc_out;
    fann_type input[2];
    ann = fann_create_from_file("xor.fann.net");

    input[0] = a;
    input[1] = b;

    calc_out = fann_run(ann, input);
    printf("and test(%f,%f)->%f\n\n", input[0], input[1], calc_out[0]);
    fann_destroy(ann);
}

int main()
{
    train();
    exec(0, 0);
    exec(0, 1);
    exec(1, 0);
    exec(1, 1);

    return 0;
}
 


//#include "../../FANN-2.2.0-Source/src/include/doublefann.h"
//#pragma comment(lib, "../../FANN-2.2.0-Source/bin/fanndouble.lib")
//
//const unsigned int NUM_INPUT = 2;
//const unsigned int NUM_OUTPUT = 1;
//const unsigned int NUM_LAYERS = 3;
//const unsigned int NUM_NEURONS_HIDDEN = 3;
//const float DESIRED_ERROR = (const float)0.0001;
//const unsigned int MAX_EPOCHS = 1000;
//const unsigned int EPOCHS_BETWEEN_REPORTS = 10;
//
//int main(int argc, char* argv[])
//{
//    struct fann* ann;
//    struct fann_train_data* data;
//
//    printf("Creating network.\n");
//    ann = fann_create_standard(NUM_LAYERS, NUM_INPUT, NUM_NEURONS_HIDDEN, NUM_OUTPUT);
//    data = fann_read_train_from_file("xor.fann");
//
//    printf("Training network.\n");
//    fann_train_on_data(ann, data, MAX_EPOCHS, EPOCHS_BETWEEN_REPORTS, DESIRED_ERROR);
//    printf("Testing network. %f\n", fann_test_data(ann, data));
//
//    //    fann_save(ann, "q:\\and_float.net");
//
//    fann_type input[2];
//    fann_type* calc_out;
//    input[0] = 0;    input[1] = 0;
//    calc_out = fann_run(ann, input);
//    printf("and test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);
//    input[0] = 0;    input[1] = 1;
//    calc_out = fann_run(ann, input);
//    printf("and test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);
//    input[0] = 1;    input[1] = 0;
//    calc_out = fann_run(ann, input);
//    printf("and test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);
//    input[0] = 1;    input[1] = 1;
//    calc_out = fann_run(ann, input);
//    printf("and test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);
//}