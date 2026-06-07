#include <string>
#include <gtest/gtest.h>
#include <cpp-subprocess/subprocess.hpp>

using std::string;
using subprocess::check_output;

TEST(Command_generate, the_result_file_can_be_generated_correctly) {
  auto outputBuffer1 = check_output({
    "../../src/differ", "look",
    "-l", "../../../asset/boy.loc", "../../../asset/girl.loc",
    "-v", "../../../asset/information.var", "../../../asset/task.var",
    "-d", "../../../asset/information.diff", "../../../asset/task.diff"
  });
  EXPECT_STREQ(outputBuffer1.buf.data(), "[Merged] Location File:\n1  %boy*=[\n2    /tmp/differ/james.md &\n3    /tmp/differ/blake.md\n4  ]\n5  %james*=[/tmp/differ/james.md]\n6  %blake*=[/tmp/differ/blake.md]\n7  %girl*=[\n8    /tmp/differ/alice.md &\n9    /tmp/differ/emma.md\n10 ]\n11 %emma*=[/tmp/differ/emma.md]\n12 %alice*=[/tmp/differ/alice.md]\n[Merged] Variable File:\n1 ^(i1)=\"personal information\"\n2 ^(i2)=\"contact\"\n3 ^(t1)=\"related tasks\"\n[Merged] Differ File:\n1  \" The data is provided by the website.\n2  | name  | age | gender | interest   | place    | height |\n3  | ----- | --- | ------ | ---------- | -------- | ------ |\n4  | alice | 29  | girl   | violin     | hamburg  | 1.68m  |\n5  | blake | 22  | boy    | reading    | paris    | 1.83m  |\n6  | emma  | 34  | girl   | skateboard | new york | 1.70m  |\n7  | james | 12  | boy    | breaking   | tokyo    | 1.79m  |\n8  \n9  ### Please confirm you #{i1}.\n10 # If your #{i1} is incorrect,please #{i2} the person below.\n11 # If you need to #{i2},it must be during working days.\n12 ={%boy}\n13 | | name  | phone       |\n14 | | ----- | ----------- |\n15 | | noah  | 12939222931 |\n16 | | liam  | 14982112929 |\n17 | | henry | 19290211919 |\n18 ={%girl}\n19 | | name  | phone       |\n20 | | ----- | ----------- |\n21 | | edith | 19329292211 |\n22 | | clara | 18929221229 |\n23 | | edith | 19329292238 |\n24 ### Below are the #{t1} for each person.\n25 - [x] Get in touch\n26 - []  Confirmation message\n27 ={%girl}\n28 | - [] Make up\n29 ={%boy}\n30 | - [] Haircut\n31 ={%alice}\n32 | - [x] Debate\n33 | - [x] Travel\n34 ={%blake}\n35 | - [x] Table tennis\n36 | - []  Cycling\n37 ={%emma}\n38 | - [x] Dance\n39 | - [x] Sing\n40 | - []  High jump\n41 ={%james}\n42 | - [x] Shopping\n43 | - [x] Long-distance running\n44 | - []  Sprint\n45 Once all #{t1} are completed,you can leave.\n");
}
