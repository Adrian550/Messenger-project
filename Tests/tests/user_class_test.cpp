#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "user.h"

// Тест функционала класса User


// Добавление контакта в список контактов
// Проверка корректного добавления
BOOST_AUTO_TEST_CASE(TEST_ADD_CONTACT)
{
	User user;

	user.add_contact("Gendiy");
	std::size_t size_constact_list = 1;

	BOOST_CHECK_EQUAL(user.current_contacts.size(), size_constact_list);
}

// Полная очистка списка контактов
// Проверка корректности очищения. 
BOOST_AUTO_TEST_CASE(TEST_CLEAR_CONTACT)
{
	User user;

	user.add_contact("Gendiy");
	user.clear_contacts();
	std::size_t size_constact_list = 0;

	BOOST_CHECK_EQUAL(user.current_contacts.size(), size_constact_list);
}


// Поиск контакта в списке контактов
// Проверка корректности поиска.
BOOST_AUTO_TEST_CASE(TEST_FIND_CONTACT)
{
	User user;

	user.add_contact("Gendiy");
	bool res_find = user.find_contact("Gendiy");

	BOOST_TEST(res_find);
}

// Удаление контакта по логину пользователя.
// Проверка корректности удаления контакта.
BOOST_AUTO_TEST_CASE(TEST_REMOVE_CONTACT)
{
	User user;

	user.add_contact("Slava");
	user.add_contact("Max");
	user.add_contact("Gendiy");

	user.remove_contact("Max");
	std::size_t size_constact_list = 2;

	BOOST_CHECK_EQUAL(user.current_contacts.size(), size_constact_list);
}

// Установление пароля.
// Проверка корректности установления пароля.
BOOST_AUTO_TEST_CASE(TEST_SET_PASSWORD)
{
	User user;
	std::string test_password = "34fj23fu8i97h";

	user.set_password("34fj23fu8i97h");

	BOOST_CHECK_EQUAL(user.get_password(), test_password);
}

// Установка логина для пользователя.
// Проверка валидности установленного пароля.
BOOST_AUTO_TEST_CASE(TEST_SET_USERNAME)
{
	User user;
	std::string test_login = "Kirill";

	user.set_username("Kirill");

	BOOST_CHECK_EQUAL(user.get_username(), test_login);
}

// Поиск контактов.
// Поиск пользователей в пустом списке контактов.
BOOST_AUTO_TEST_CASE(TEST_FIND_EMPTY_CONTACT)
{
	User user;
	bool test_result_empty_find = false;

	bool res_find = user.find_contact("Maxim");

	BOOST_TEST(test_result_empty_find == res_find);
}

// Установка пользователю индификатора
// Проверка корректности установки уникального индификатора для текущей сессии пользователя.
BOOST_AUTO_TEST_CASE(TEST_SET_USER_ID)
{
	User user;
	std::string test_id = "5";

	user.set_user_id("5");

	BOOST_CHECK_EQUAL(user.get_user_id(), test_id);
}

// Удаление контакта.
// Проверка валидного удаления юзера из пустого списка контактов
BOOST_AUTO_TEST_CASE(TEST_REMOVE_NOT_EXIST_CONTACT)
{
	User user;
	std::size_t size_constact_list = 3;


	user.add_contact("Slava");
	user.add_contact("Max");
	user.add_contact("Gendiy");

	user.remove_contact("Andrey");

	BOOST_CHECK_EQUAL(user.current_contacts.size(), size_constact_list);
}


// Поиск по контактам.
// Проверка поиска по заполненному списку контактов несуществующего пользователя.
BOOST_AUTO_TEST_CASE(TEST_FIND_NOT_EXIST_USER)
{
	User user;
	bool search_res = false;

	user.add_contact("Slava");
	user.add_contact("Max");
	user.add_contact("Gendiy");
	user.add_contact("Sergey");
	user.add_contact("Kirill");
	user.add_contact("Vasya");
	user.add_contact("Lesha");
	user.add_contact("Артем");
	user.add_contact("Илья");
	user.add_contact("Леша");

	bool res_find = user.find_contact("Константин");

	BOOST_TEST(search_res == res_find);
}