#include "filestream.h"
#include "variant.h"
#include "gtest/gtest.h"

namespace RabidSQL {

class TestVariant : public ::testing::Test {
protected:
    void SetUp()
    {
        filename = "/tmp/rabidsql-test-variant";
    }

    void TearDown()
    {
        // Unlink temp file
        std::remove(filename.c_str());
    }

    std::string filename;
};

// Tests converting a string to a variant vector
TEST_F(TestVariant, ConvertStringVariantToVariantVector) {
    Variant value("test");
    EXPECT_EQ(value, value.toVariantVector());
}

// Tests converting a string to a string vector
TEST_F(TestVariant, ConvertStringVariantToStringVector) {
    Variant value("test");
    EXPECT_EQ(value, value.toStringVector());
}

// Tests converting a string vector to a variant vector
TEST_F(TestVariant, ConvertStringVectorToVariantVector) {
    std::vector<std::string> list;
    list.push_back("test");
    Variant value(list);
    EXPECT_EQ(value, value.toVariantVector());
}

// Tests converting a variant vector to a string vector
TEST_F(TestVariant, ConvertVariantVectorToStringVector) {
    std::vector<std::string> list;
    list.push_back("test");
    Variant value(list);
    EXPECT_EQ(value, value.toStringVector());
}

// Tests that the Variant::operator== method works for int-int comparison
TEST_F(TestVariant, OperatorEQIntInt) {
    Variant v1(124);
    Variant v2(124);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for int-double comparison
TEST_F(TestVariant, OperatorEQIntDouble) {
    Variant v1(124);
    Variant v2((double) 124.0);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for int-float comparison
TEST_F(TestVariant, OperatorEQIntFloat) {
    Variant v1(124);
    Variant v2((float) 124.0);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for int-string comparison
TEST_F(TestVariant, OperatorEQIntString) {
    Variant v1(124);
    Variant v2("124");
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for string-int comparison
TEST_F(TestVariant, OperatorEQStringInt) {
    Variant v1("124");
    Variant v2(124);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for float-string comparison
TEST_F(TestVariant, OperatorEQFloatString) {
    Variant v1((float) 124.0);
    Variant v2("124.00");
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for string-float comparison
TEST_F(TestVariant, OperatorEQStringFloat) {
    Variant v1("124.00");
    Variant v2((float) 124.0);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for double-float comparison
TEST_F(TestVariant, OperatorEQDoubleFloat) {
    Variant v1((double) 124.8);
    Variant v2((float) 124.8);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for float-double comparison
TEST_F(TestVariant, OperatorEQFloatDouble) {
    Variant v1((float) 124.8);
    Variant v2((double) 124.8);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for float-string vector
// comparison
TEST_F(TestVariant, OperatorEQFloatVariantVector) {
    Variant v1((float) 124.8);
    Variant v2(VariantVector() << (float) 124.8);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for float-string vector
// comparison
TEST_F(TestVariant, OperatorEQFloatVariantVectorMultiElements) {
    Variant v1((float) 124.8);
    Variant v2(VariantVector() << (float) 124.8 << "1");
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for variant vector-variant
// vector comparison
TEST_F(TestVariant, OperatorEQVariantVectorVariantVector) {
    Variant v1(VariantVector() << (float) 124.8 << "1" << (double) 7);
    Variant v2(VariantVector() << (float) 124.8 << "1" << (double) 7);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for variant vector-variant
// vector comparison w/ typecasting
TEST_F(TestVariant, OperatorEQVariantVectorVariantVectorTypeCasting) {
    Variant v1(VariantVector() << (float) 124.8 << "1.0" << (double) 7);
    Variant v2(VariantVector() << (float) 124.8 << 1.0 << (double) 7);
    EXPECT_EQ(v1, v2);

    Variant v3(VariantVector() << (float) 124.8 << "1" << (double) 7);
    Variant v4(VariantVector() << (float) 124.8 << (float) 1.0 << (double) 7);
    EXPECT_EQ(v3, v4);
}

// Tests that the Variant::operator== method works for variant vector-string
// vector comparison
TEST_F(TestVariant, OperatorEQVariantVectorStringVector) {
    Variant v1(VariantVector() << (float) 124.8 << "1" << (double) 7);
    std::vector<std::string> list;
    list.push_back("124.8");
    list.push_back("1");
    list.push_back("7");
    Variant v2(list);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator== method works for float-double comparison
TEST_F(TestVariant, OperatorNEFloatDouble) {
    Variant v1((float) 124.8);
    Variant v2((double) 124.7);
    EXPECT_NE(v1, v2);
}

// Tests that the Variant::operator!= method works for variant vector-variant
// vector comparison w/ typecasting
TEST_F(TestVariant, OperatorNEVariantVectorVariantVectorTypeCasting) {
    Variant v1(VariantVector() << (float) 7);
    Variant v2(VariantVector() << (double) 7.5);
    EXPECT_NE(v1, v2);
}

// Tests that the Variant::operator== method works for string vector-variant
// vector comparison
TEST_F(TestVariant, OperatorEQStringVectorVariantVector) {
    std::vector<std::string> list;
    list.push_back("124.8");
    list.push_back("1");
    list.push_back("7");
    Variant v1(list);
    Variant v2(VariantVector() << (float) 124.8 << "1" << (double) 7);
    EXPECT_EQ(v1, v2);
}

// Tests that the Variant::operator!= method works for blank string("")-nullptr
TEST_F(TestVariant, OperatorNEBlankStringnullptr) {
    Variant v1("");
    Variant v2;
    EXPECT_NE(v1, v2);
}

// Tests that the Variant::operator!= method works for nullptr-blank int(0)
TEST_F(TestVariant, OperatorNEnullptrBlankInt) {
    Variant v1;
    Variant v2(0);
    EXPECT_NE(v1, v2);
}

// Tests that the Variant::operator> method works for float-double comparison
TEST_F(TestVariant, OperatorGTFloatFloat) {
    Variant v1((float) 124.09);
    Variant v2((float) 124.08);
    EXPECT_GT(v1, v2);
}

// Tests that the Variant::operator> method works for float-double comparison
TEST_F(TestVariant, OperatorGTFloatDouble) {
    Variant v1((float) 124.09);
    Variant v2((double) 124.08);
    EXPECT_GT(v1, v2);
}

// Tests that the Variant::operator> method works for double-float comparison
TEST_F(TestVariant, OperatorGTDoubleFloat) {
    Variant v1((double) 124.09);
    Variant v2((float) 124.08);
    EXPECT_GT(v1, v2);
}

// Tests that the Variant::operator> method works for string-float comparison
TEST_F(TestVariant, OperatorGTStringFloat) {
    Variant v1("124.09");
    Variant v2((float) 124.08);
    EXPECT_GT(v1, v2);
}

// Tests that the Variant::operator> method works for float-string comparison
TEST_F(TestVariant, OperatorGTFloatString) {
    Variant v1((float) 124.09);
    Variant v2("124.08");
    EXPECT_GT(v1, v2);
}

// Tests that the Variant::operator< method works for float-float comparison
TEST_F(TestVariant, OperatorLTFloatFloatP1) {
    Variant v1((float) 124.8);
    Variant v2((float) 124.9);
    EXPECT_LT(v1, v2);
}

// Tests that the Variant::operator< method works for float-double comparison
TEST_F(TestVariant, OperatorLTFloatFloat) {
    Variant v1((float) 124.08);
    Variant v2((double) 124.09);
    EXPECT_LT(v1, v2);
}

// Tests that the Variant::operator< method works for float-double comparison
TEST_F(TestVariant, OperatorLTFloatDouble) {
    Variant v1((float) 124.08);
    Variant v2((double) 124.09);
    EXPECT_LT(v1, v2);
}

// Tests that the Variant::operator< method works for double-float comparison
TEST_F(TestVariant, OperatorLTDoubleFloat) {
    Variant v1((double) 124.08);
    Variant v2((float) 124.09);
    EXPECT_LT(v1, v2);
}

// Tests that the Variant::operator< method works for string-float comparison
TEST_F(TestVariant, OperatorLTStringFloat) {
    Variant v1("124.08");
    Variant v2((float) 124.09);
    EXPECT_LT(v1, v2);
}

// Tests that the Variant::operator< method works for float-string comparison
TEST_F(TestVariant, OperatorLTFloatString) {
    Variant v1((float) 124.08);
    Variant v2("124.09");
    EXPECT_LT(v1, v2);
}

// This test macro is the same for all single type tests. It is very similar to
// the multi-type test (VariantFileIO.BinaryIOMultipleTypes). Please see that
// for functionality comments.

#define TEST_BINARY_SINGLE(T, V) \
    BinaryStream stream; \
    T value = V; \
    Variant variant(value); \
    stream.open(filename, std::ios::out); \
    stream << variant; \
    stream.close(); \
    variant = "a value that must not conflict with the tests"; \
    stream.open(filename, std::ios::in); \
    stream >> variant; \
    stream.close(); \
    EXPECT_EQ(variant, value); \
    char tc; \
    EXPECT_FALSE(stream.get(tc)); \
    EXPECT_TRUE(stream.eof());

// Tests reading and writing of a single nullptr variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIONull) {
    TEST_BINARY_SINGLE(std::nullptr_t, nullptr);
}

// Tests reading and writing of a single String variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOString) {
    TEST_BINARY_SINGLE(std::string, "test");
}

// Tests reading and writing of a single String vector variant from and to
// binary files
TEST_F(TestVariant, FileIOBinaryIOStringVector) {
    std::vector<std::string> vector;
    vector.push_back("value 1");
    vector.push_back("value 2");
    TEST_BINARY_SINGLE(std::vector<std::string>, vector);
}

// Tests reading and writing of a single Variant vector variant from and to
// binary files
TEST_F(TestVariant, FileIOBinaryIOVariantVector) {
    TEST_BINARY_SINGLE(VariantVector, VariantVector() << "test" << 123
        << nullptr);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOULong) {
    TEST_BINARY_SINGLE(unsigned long, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOLong) {
    TEST_BINARY_SINGLE(long, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOUInt) {
    TEST_BINARY_SINGLE(unsigned int, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOInt) {
    TEST_BINARY_SINGLE(int, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOUShort) {
    TEST_BINARY_SINGLE(unsigned short, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOShort) {
    TEST_BINARY_SINGLE(short, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOFloat) {
    TEST_BINARY_SINGLE(float, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIODouble) {
    TEST_BINARY_SINGLE(float, 1);
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOQueryResult) {
    TEST_BINARY_SINGLE(QueryResult, QueryResult());
}

// Tests reading and writing of a single long variant from and to binary files
TEST_F(TestVariant, FileIOBinaryIOMultipleTypes) {
    BinaryStream stream;

    // Values we'll be testing for
    long value1 = 123;
    std::string value2 = "test";
    auto value3 = nullptr;

    // Initialize variants
    Variant variant1(value1);
    Variant variant2(value2);
    Variant variant3(value3);

    // Open stream for writing
    stream.open(filename, std::ios::out);

    // Write variants
    stream << variant1;
    stream << variant2;
    stream << variant3;

    // Close stream
    stream.close();

    // Open stream for reading
    stream.open(filename, std::ios::in);

    // Initialize a final variant for storage of data read from the stream
    Variant variant("a value that must not conflict with the tests");

    stream >> variant;
    EXPECT_EQ(variant, value1);

    stream >> variant;
    EXPECT_EQ(variant, value2);

    stream >> variant;
    EXPECT_EQ(variant, value3);

    // Lets make sure this was all the data. We need to read again to set the
    // EOF bit
    char tc;
    EXPECT_FALSE(stream.get(tc));

    // Ensure EOF
    EXPECT_TRUE(stream.eof());

    // Close stream
    stream.close();
}

} // namespace RabidSQL

