//
// fann_test.c : 
// FANN 测试
//
// 到下面的网站下载FANN库:
//   Fast Artificial Neural Network Library (fann)
//     http://leenissen.dk/fann/
//   下载链接: Download FANN --->  C Source Code and Windows DLL files 
//
#include "../FANN-2.2.0-Source/src/include/doublefann.h"
//#ifdef _DEBUG
//#pragma comment(lib, "../fann-2.0.0/MicrosoftWindowsDll/bin/fanndoubleMTd.lib")
//#else
//#pragma comment(lib, "../fann-2.0.0/MicrosoftWindowsDll/bin/fanndoubleMT.lib")
//#endif

#pragma comment(lib, "../FANN-2.2.0-Source/bin/fanndouble.lib")
// 
// 训练:
// 加法神经网络
// c = a+b;
void train()
{
    const unsigned int num_input = 2;       // 输入项个数
    const unsigned int num_output = 1;      // 输出项个数
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 3;
    const float desired_error = (const float)0.00000001;
    const unsigned int max_epochs = 500000; // 最多执行次数   
    const unsigned int epochs_between_reports = 10000;   // 报告频率

    struct fann* ann;

    int     Num = 200;
    float   Mf = Num * 3.f;
    int     i;
    double  a, b, c;
    FILE* fp;
    fopen_s(&fp, "add.fann", "w");
    fprintf_s(fp, "%d 2 1\n", Num);
    // 生成训练文件
    for (i = 1; i <= Num; i++) {
        // 生成2个数, 要求在(0,1)之间
        a = i / Mf;
        b = (i + 1) / Mf;
        c = a + b;    // 要求在(0,1)之间

        // 输入内容写到训练文件
        fprintf_s(fp, "%lf %lf\n%lf\n", a, b, c);
    }
    fclose(fp);
    // 样本训练
    ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_LINEAR);
    fann_set_activation_function_output(ann, FANN_LINEAR);
    fann_train_on_file(ann, "add.fann", max_epochs, epochs_between_reports, desired_error);
    fann_save(ann, "add.fann.net");
    fann_destroy(ann);
}
// 执行:
// 测试
void exec(double a, double b)
{
    struct fann* ann;

    fann_type* calc_out;
    fann_type input[2];
    ann = fann_create_from_file("add.fann.net");

    input[0] = a;
    input[1] = b;

    calc_out = fann_run(ann, input);
    fann_destroy(ann);
    printf("a=%f\nb=%f\nc=%f\n期望值c=%f\n\n", input[0], input[1], calc_out[0], input[0] + input[1]);
}
//
// 主程序
//
int main()
{
    // 下面的方法只需调用一次, 然后注释掉
     train();
    exec(0.354, 0.58934);
    exec(0.21469, 0.3914968);
    exec(0.130, 0.44);
    exec(-0.3654, 0.58455);
    exec(0.365420, -0.95);
    return 0;
}