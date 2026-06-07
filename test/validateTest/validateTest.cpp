#include <string>
#include <gtest/gtest.h>
#include <cpp-subprocess/subprocess.hpp>

using std::string;
using subprocess::check_output;

TEST(Command_generate, the_result_file_can_be_generated_correctly) {
  auto outputBuffer1 = check_output({
    "../../src/differ", "validate",
    "-l", "../../../asset/boy.loc", "../../../asset/girl.loc",
    "-v", "../../../asset/information.var", "../../../asset/task.var",
    "-d", "../../../asset/information.diff", "../../../asset/task.diff"
  });
  EXPECT_STREQ(outputBuffer1.buf.data(), "[Validation] :: \xE2\x9C\x94 \"/home/leo/differ/build/test/validateTest/../../../asset/boy.loc\";\n[Validation] :: \xE2\x9C\x94 \"/home/leo/differ/build/test/validateTest/../../../asset/girl.loc\";\n[Validation] :: \xE2\x9C\x94 \"/home/leo/differ/build/test/validateTest/../../../asset/information.var\";\n[Validation] :: \xE2\x9C\x94 \"/home/leo/differ/build/test/validateTest/../../../asset/task.var\";\n[Validation] :: \xE2\x9C\x94 \"/home/leo/differ/build/test/validateTest/../../../asset/information.diff\";\n[Validation] :: \xE2\x9C\x94 \"/home/leo/differ/build/test/validateTest/../../../asset/task.diff\";\n");
}
