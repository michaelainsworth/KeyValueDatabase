#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE kvp

#include <boost/test/unit_test.hpp>
#include <cassert>
#include <iostream>
#include <Kvp/Kvp.hpp>

using namespace Kvp;
using namespace std;

// ============================================================================
// Fixtures
// ============================================================================

struct BaseFixture
{

    BaseFixture()
        : db()
        , key("key")
        , value1("value1"), value2("value2"), value3("value3")
        , atom0(0), atom1(1), atom2(2), atom3(3) {}

    Database db;
    Atom atom0;
    Key key;
    Value value1;
    Value value2;
    Value value3;
    Atom atom1;
    Atom atom2;
    Atom atom3;

};

struct NoValues : BaseFixture
{

    NoValues() : BaseFixture() {}

};

struct OneValue : BaseFixture
{

    OneValue() : BaseFixture()
    {
        db.create(key, value1, atom1);
    }

};

// ============================================================================
// Test Suite
// ============================================================================

BOOST_AUTO_TEST_SUITE(kvp)

// ----------------------------------------------------------------------------
// Test read()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_read_on_a_non_existant_key_returns_an_empty_current_value,
    NoValues
)
{
    CurrentValue cv = db.read(Key("foo"));
    BOOST_REQUIRE(!cv);
    BOOST_REQUIRE(!cv.exists());
    BOOST_REQUIRE(0 == cv.value().toString().size());
    BOOST_REQUIRE(atom0 == cv.atom());
}

BOOST_FIXTURE_TEST_CASE
(
    calling_read_on_an_existing_key_returns_the_correct_value,
    OneValue
)
{
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(cv);
    BOOST_REQUIRE(cv.exists());
    BOOST_REQUIRE(value1 == cv.value());
    BOOST_REQUIRE(atom1 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test create()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_create_returns_the_newly_created_value,
    NoValues
)
{
    db.create(key, value1, atom1);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(cv);
    BOOST_REQUIRE(cv.exists());
    BOOST_REQUIRE(value1 == cv.value());
    BOOST_REQUIRE(atom1 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test create() -> create()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_create_then_create_throws_a_concurrency_error,
    NoValues
)
{
    db.create(key, value1, atom1);
    BOOST_REQUIRE_THROW(db.create(key, value1, atom1), ConcurrencyError);
}

// ----------------------------------------------------------------------------
// Test create() -> update()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_create_then_update_with_an_incorrect_atom_condition_throws_a_concurrency_error,
    NoValues
)
{
    db.create(key, value1, atom1);
    BOOST_REQUIRE_THROW(db.update(key, value1, atom1, atom2), ConcurrencyError);
}

BOOST_FIXTURE_TEST_CASE
(
    calling_create_then_update_returns_the_most_recent_value,
    NoValues
)
{
    db.create(key, value1, atom1);
    db.update(key, value2, atom2, atom1);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(cv);
    BOOST_REQUIRE(cv.exists());
    BOOST_REQUIRE(value2 == cv.value());
    BOOST_REQUIRE(atom2 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test create() -> delet()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_create_then_delet_with_an_incorrect_atom_condition_throws_a_concurrency_error,
    NoValues
)
{
    db.create(key, value1, atom1);
    BOOST_REQUIRE_THROW(db.delet(key, atom2), ConcurrencyError);
}

BOOST_FIXTURE_TEST_CASE
(
    calling_create_then_delete_returns_an_empty_value_and_atom,
    NoValues
)
{
    db.create(key, value1, atom1);
    db.delet(key, atom1);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(!cv);
    BOOST_REQUIRE(!cv.exists());
    BOOST_REQUIRE(0 == cv.value().toString().size());
    BOOST_REQUIRE(atom0 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test update()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_update_with_an_incorrect_atom_condition_throws_a_concurrency_error,
    OneValue
)
{
    BOOST_REQUIRE_THROW(db.update(key, value2, atom2, atom3), ConcurrencyError);
}

BOOST_FIXTURE_TEST_CASE
(
    calling_update_returns_the_most_recent_value_and_atom,
    OneValue
)
{
    db.update(key, value2, atom2, atom1);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(cv);
    BOOST_REQUIRE(cv.exists());
    BOOST_REQUIRE(value2 == cv.value());
    BOOST_REQUIRE(atom2 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test update() -> create()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_update_then_create_throws_a_concurrency_error,
    OneValue
)
{
    db.update(key, value2, atom2, atom1);
    BOOST_REQUIRE_THROW(db.create(key, value1, atom1), ConcurrencyError);
}

// ----------------------------------------------------------------------------
// Test update() -> update()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_update_then_update_with_an_incorrect_atom_condition_throws_a_concurrency_error,
    OneValue
)
{
    BOOST_REQUIRE_THROW(db.update(key, value2, atom2, atom3),
            ConcurrencyError);
}

BOOST_FIXTURE_TEST_CASE
(
    calling_update_then_update_returns_the_original_value_and_atom,
    OneValue
)
{
    db.update(key, value2, atom2, atom1);
    db.update(key, value3, atom3, atom2);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(cv);
    BOOST_REQUIRE(cv.exists());
    BOOST_REQUIRE(value3 == cv.value());
    BOOST_REQUIRE(atom3 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test update() -> delet()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_update_then_delet_with_an_incorrect_atom_condition_throws_a_concurrency_error,
    OneValue
)
{
    db.update(key, value2, atom2, atom1);
    BOOST_REQUIRE_THROW(db.delet(key, atom1), ConcurrencyError);
}

BOOST_FIXTURE_TEST_CASE
(
    calling_update_then_delet_returns_an_empty_value_and_atom,
    OneValue
)
{
    db.update(key, value2, atom2, atom1);
    db.delet(key, atom2);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(!cv);
    BOOST_REQUIRE(!cv.exists());
    BOOST_REQUIRE(0 == cv.value().toString().size());
    BOOST_REQUIRE(atom0 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test delet()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_delet_on_a_non_existant_key_throws_a_concurrency_error,
    NoValues
)
{
    BOOST_REQUIRE_THROW(db.delet(key, atom1), ConcurrencyError);
}

BOOST_FIXTURE_TEST_CASE
(
    calling_delet_with_an_incorrect_atom_condition_throws_a_concurrency_error,
    OneValue
)
{
    BOOST_REQUIRE_THROW(db.delet(key, atom2), ConcurrencyError);
}

// ----------------------------------------------------------------------------
// Test delet() -> create()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_delet_then_create_returns_the_new_value_and_atom,
    OneValue
)
{
    db.delet(key, atom1);
    db.create(key, value2, atom2);
    CurrentValue cv = db.read(key);
    BOOST_REQUIRE(cv);
    BOOST_REQUIRE(cv.exists());
    BOOST_REQUIRE(value2 == cv.value());
    BOOST_REQUIRE(atom2 == cv.atom());
}

// ----------------------------------------------------------------------------
// Test delet() -> update()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_delet_then_update_throws_a_concurrency_error,
    OneValue
)
{
    db.delet(key, atom1);
    BOOST_REQUIRE_THROW(db.update(key, value2, atom2, atom1),
            ConcurrencyError);
}

// ----------------------------------------------------------------------------
// Test delet() -> delet()
// ----------------------------------------------------------------------------

BOOST_FIXTURE_TEST_CASE
(
    calling_delet_then_delet_throws_a_concurrency_error,
    OneValue
)
{
    db.delet(key, atom1);
    BOOST_REQUIRE_THROW(db.delet(key, atom1), ConcurrencyError);
}

BOOST_AUTO_TEST_SUITE_END()

