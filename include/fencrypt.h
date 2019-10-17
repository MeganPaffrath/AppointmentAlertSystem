/*
 * fencrypt.h
 *
 *  Created on: Oct 2, 2019
 *      Author: jjyoy
 */

#ifndef FENCRYPT_H_
#define FENCRYPT_H_


//======================================================================================================
//		fencrypt Header		//
//===========================
//
//		Encrypts data using Bitwise XOR + Bitwise NOT on data passed into the function.
//
//		The data passed into the function is encrypted by being bitwise XOR'ed with the key,
//		then bitwise NOT'ed.
//
//		The decryption process is the exact opposite of encryption.
//
//
//	------------------
//	|	Functions	/
//	----------------
//
//		encrypt(string& data_, string key) 			Encrypts the data with the key specified.
//													Returns the encrypted string.
//
//		decrypt(string& data_, string key)			Decrypts the data with the key specified.
//													Returns the decrypted string.
//
//
//======================================================================================================





#include <iostream>
#include <fstream>
using namespace std;


string encrypt(string& data_, string key)
{
	string temp = key;

	while (temp.size() < data_.size())
	{temp += key;}


	for (unsigned int i = 0; i < data_.size(); ++i)
	{data_[i] ^= temp[i];}

	for(unsigned int i = 0; i < data_.size(); i++)
	{data_[i] = ~data_[i];}

	return data_;
}

string decrypt(string& data_, string key)
{
	string temp = key;

	for(unsigned int i = 0; i < data_.size(); i++)
	{data_[i] = ~data_[i];}

	while (temp.size() < data_.size())
	{temp += key;}

	for (unsigned int i = 0; i < data_.size(); ++i)
	{data_[i] ^= temp[i];}

	return data_;
}



#endif /* FENCRYPT_H_ */
