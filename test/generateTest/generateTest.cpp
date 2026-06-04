#include <string>
#include <gtest/gtest.h>
#include <cpp-subprocess/subprocess.hpp>

using std::string;
using subprocess::check_output;

TEST(Command_generate, the_result_file_can_be_generated_correctly) {
  auto outputBuffer1 = check_output({
    "../../src/differ", "generate",
    "-l", "../../../asset/boy.loc", "../../../asset/girl.loc",
    "-v", "../../../asset/information.var", "../../../asset/task.var",
    "-d", "../../../asset/information.diff", "../../../asset/task.diff"
  });
  EXPECT_STREQ(outputBuffer1.buf.data(), "[Generate] :: \xE2\x9C\x94 \"/tmp/differ/blake.md\";\n[Generate] :: \xE2\x9C\x94 \"/tmp/differ/emma.md\";\n[Generate] :: \xE2\x9C\x94 \"/tmp/differ/james.md\";\n[Generate] :: \xE2\x9C\x94 \"/tmp/differ/alice.md\";\n");
  auto outputBuffer2 = check_output({"cat", "/tmp/differ/blake.md"});
  EXPECT_STREQ(outputBuffer2.buf.data(), "| name  | age | gender | interest   | place    | height |\n| ----- | --- | ------ | ---------- | -------- | ------ |\n| alice | 29  | girl   | violin     | hamburg  | 1.68m  |\n| blake | 22  | boy    | reading    | paris    | 1.83m  |\n| emma  | 34  | girl   | skateboard | new york | 1.70m  |\n| james | 12  | boy    | breaking   | tokyo    | 1.79m  |\n\n### Please confirm you personal information.\n# If your personal information is incorrect,please contact the person below.\n# If you need to contact,it must be during working days.\n| name  | phone       |\n| ----- | ----------- |\n| noah  | 12939222931 |\n| liam  | 14982112929 |\n| henry | 19290211919 |\n### Below are the related tasks for each person.\n- [x] Get in touch\n- []  Confirmation message\n- [] Haircut\n- [x] Table tennis\n- []  Cycling\nOnce all related tasks are completed,you can leave.\n");
  auto outputBuffer3 = check_output({"cat", "/tmp/differ/emma.md"});
  EXPECT_STREQ(outputBuffer3.buf.data(), "| name  | age | gender | interest   | place    | height |\n| ----- | --- | ------ | ---------- | -------- | ------ |\n| alice | 29  | girl   | violin     | hamburg  | 1.68m  |\n| blake | 22  | boy    | reading    | paris    | 1.83m  |\n| emma  | 34  | girl   | skateboard | new york | 1.70m  |\n| james | 12  | boy    | breaking   | tokyo    | 1.79m  |\n\n### Please confirm you personal information.\n# If your personal information is incorrect,please contact the person below.\n# If you need to contact,it must be during working days.\n| name  | phone       |\n| ----- | ----------- |\n| edith | 19329292211 |\n| clara | 18929221229 |\n| edith | 19329292238 |\n### Below are the related tasks for each person.\n- [x] Get in touch\n- []  Confirmation message\n- [] Make up\n- [x] Dance\n- [x] Sing\n- []  High jump\nOnce all related tasks are completed,you can leave.\n");
  auto outputBuffer4 = check_output({"cat", "/tmp/differ/james.md"});
  EXPECT_STREQ(outputBuffer4.buf.data(), "| name  | age | gender | interest   | place    | height |\n| ----- | --- | ------ | ---------- | -------- | ------ |\n| alice | 29  | girl   | violin     | hamburg  | 1.68m  |\n| blake | 22  | boy    | reading    | paris    | 1.83m  |\n| emma  | 34  | girl   | skateboard | new york | 1.70m  |\n| james | 12  | boy    | breaking   | tokyo    | 1.79m  |\n\n### Please confirm you personal information.\n# If your personal information is incorrect,please contact the person below.\n# If you need to contact,it must be during working days.\n| name  | phone       |\n| ----- | ----------- |\n| noah  | 12939222931 |\n| liam  | 14982112929 |\n| henry | 19290211919 |\n### Below are the related tasks for each person.\n- [x] Get in touch\n- []  Confirmation message\n- [] Haircut\n- [x] Shopping\n- [x] Long-distance running\n- []  Sprint\nOnce all related tasks are completed,you can leave.\n");
  auto outputBuffer5 = check_output({"cat", "/tmp/differ/alice.md"});
  EXPECT_STREQ(outputBuffer5.buf.data(), "| name  | age | gender | interest   | place    | height |\n| ----- | --- | ------ | ---------- | -------- | ------ |\n| alice | 29  | girl   | violin     | hamburg  | 1.68m  |\n| blake | 22  | boy    | reading    | paris    | 1.83m  |\n| emma  | 34  | girl   | skateboard | new york | 1.70m  |\n| james | 12  | boy    | breaking   | tokyo    | 1.79m  |\n\n### Please confirm you personal information.\n# If your personal information is incorrect,please contact the person below.\n# If you need to contact,it must be during working days.\n| name  | phone       |\n| ----- | ----------- |\n| edith | 19329292211 |\n| clara | 18929221229 |\n| edith | 19329292238 |\n### Below are the related tasks for each person.\n- [x] Get in touch\n- []  Confirmation message\n- [] Make up\n- [x] Debate\n- [x] Travel\nOnce all related tasks are completed,you can leave.\n");
}
