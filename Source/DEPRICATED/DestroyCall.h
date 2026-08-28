/*!
\file   DestroyCall.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   1-30-2023
\brief
        Functions for maintaining a `DestroyCall`
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include <stack>

/*!
\class  DestroyCall
\brief
       Class that, when deleted, calls delete on many other objects
*/
class DestroyCall{
    public:

		/*!
		\fn     DestroyCall()
		\par    This function has no parameters.
		\return Constructed `DestroyCall`
		\brief
		        This function constructs the new `DestroyCall`.
		*/
        DestroyCall();

		/*!
		\fn     ~DestroyCall()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs the `DestroyCall`.
		*/
        ~DestroyCall();

		/*!
		\class  Deleter
		\brief
		        Wrapper class that deletes an object
		*/
		class Deleter{
			public:

				/*!
				\fn     virtual ~Deleter()
				\par    This function has no parameters.
				\return Nothing
				\brief
				        This function destructs the `DestroyCall`.
				*/
				virtual ~Deleter() = 0;

		};

		/*!
		\class  DeleterTemp
		\tparam Type
		          Type of object to be deleted
		\brief
		        Template class that deletes an object of a specific type
		*/
		template<typename Type> class DeleterTemp : public Deleter{
			public:

				/*!
				\fn     DeleterTemp(Type *object)
				\param  object
				          Object to delete
				\return Constructed `DeleterTemp`
				\brief
				        This function constructs the `DeleterTemp`.
				*/
				DeleterTemp(Type *object);

				/*!
				\fn     ~DeleterTemp()
				\par    This function has no parameters.
				\return Nothing
				\brief
				        This function destructs the `DestroyCall`.
				*/
				~DeleterTemp() override;

			private:

				/*!
				\var    object
				          Object to delete
				*/
				Type *object;

		};

		/*!
		\fn     template<typename Type>void add(Type *dependent)
		\tparam Type
		          Type of object to add
		\param  dependent
		          Object to add
		\return Nothing
		\brief
		        This function adds an object to be deleted.
		*/
        template<typename Type> void add(Type *dependent);

	private:

		/*!
		\var    dependents
		          List of objects to be deleted with the `DestroyCall`
		*/
		std::stack<Deleter *> dependents;

};

#include "DestroyCallTemplates.cpp"