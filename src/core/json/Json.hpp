#pragma once

#include "core/RefCounted.hpp"
#include "core/StringUtil.hpp"
#include "core/Type.hpp"
#include <map>
#include <vector>

using JsonIntType = uint64_t;
using JsonFloatType = double;

class JsonBase : public RefCounted
{
    public:
    
        typedef ref< JsonBase > Ref;

        enum class Type { Null, Class, Array, String, Integer, Real, Boolean };

        inline Type GetType( void ) const { return mType; }
    
        virtual const std::string GetString( ) { return std::string(); }
    
        // Formatted for debugging
    
        virtual const std::string Dump( JsonIntType indent ) = 0;
    
        // Mimized
    
        virtual const std::string Stringify( ) const = 0;

        virtual JsonIntType GetCount( void ) { return 0; }
        virtual Ref GetAt( JsonIntType i ) { return NULL; }
    
    	virtual void push_back( Arg< JsonBase::Ref >::Type refValue ) { }
    
        virtual Ref GetValueForKey( Arg< std::string >::Type key );
        virtual void SetValueForKey( Arg< std::string >::Type key, Arg< JsonBase::Ref >::Type refJson );
    	virtual void SetIntegerValueForKey( Arg< std::string >::Type key, Arg< JsonIntType >::Type val );
        virtual void SetStringValueForKey( Arg< std::string >::Type key, Arg< std::string >::Type val );
    
        virtual Ref GetFirst( ) { return NULL; }
        virtual Ref GetNext( ) { return NULL; }

        virtual const bool GetBool( ) { return false; }
        virtual const JsonFloatType GetFloat64( void ) { return 0.0; }
        virtual const JsonIntType GetUInt( void ) { return 0; }
    
        virtual ~JsonBase( ) { }
    
    protected:
    
        JsonBase( Type type ) : mType( type ) { }
    
    private:
    
        Type mType;
};

class JsonNull : public JsonBase
{
    public:
    
        JsonNull( void ) : JsonBase( Type::Null ) { }
    
        virtual const std::string Dump( JsonIntType indent )
        {
            return Sl( "null" );
        }
    
        virtual const std::string Stringify( ) const
        {
        	return Sl( "null" );
    	}
};

class JsonString : public JsonBase
{
    public:
    
        inline JsonString( Arg< std::string >::Type s ) : JsonBase( Type::String ), mString( s ) { }
    
        virtual const std::string GetString( void ) { return mString; }
    
        virtual const std::string Dump( JsonIntType i )
        {
            return Fs( "\"%s\"", mString.c_str() );
        }
    
        virtual const std::string Stringify( ) const
    	{
        	const std::string s =
            	Sl( "\"" ) +
                OmStringEscape( mString, OM_STRING_C_ESCAPE_ITEMS ) +
                Sl( "\"" );
            
            return s;
    	}
    
    private:
    
        std::string mString;
};

class JsonInteger : public JsonBase
{
    public:
    
        inline JsonInteger( JsonIntType value )
            :
            JsonBase( Type::Integer ),
            mValue( value )
        { }
    
        virtual const std::string Dump( JsonIntType i )
        {
            return Fs( "%i", (int) mValue );
        }
    
    	virtual const std::string Stringify( ) const
    	{
        	return Fs( "%i", (int) mValue );
        }
    
        virtual const JsonFloatType GetFloat64( void )
        {
            return static_cast< JsonFloatType >( mValue );
        }
    
        virtual const JsonIntType GetUInt( void )
        {
            return static_cast< JsonIntType >( mValue );
        }
    
    private:
    
        JsonIntType mValue;
        
};

class JsonReal : public JsonBase
{
    public:
    
        inline JsonReal( JsonFloatType real ) : JsonBase( Type::Real ), mReal( real ) { }
    
        virtual const std::string Dump( JsonIntType indent )
        {
            return Stringify();
        }
    
        virtual const std::string Stringify(  ) const
        {
            return Fs( "%g", mReal );
        }
    
        virtual const JsonFloatType GetFloat64( void )
        {
            return mReal;
        }
    
        virtual const JsonIntType GetUInt( void )
        {
            return static_cast< JsonIntType >( mReal );
        }    
    
    private:
    
        JsonFloatType mReal;
};


class JsonBoolean : public JsonBase
{
    public:
    
        inline JsonBoolean( bool value ) : JsonBase( Type::Boolean ), mValue( value ) { }
    
        virtual const std::string Dump( JsonIntType indent )
        {
        	return Stringify();
        }
    
        virtual const std::string Stringify( ) const
    	{
            return mValue ? Sl( "true" ) : Sl( "false" );
        }
    
        virtual const bool GetBool( void )
        {
            return mValue;
        }
    
    private:
    
        bool mValue;
};

class JsonObject : public JsonBase
{
    public:
    
        typedef std::map< std::string, JsonBase::Ref > DictType;
    
        inline JsonObject( void ) : JsonBase( Type::Class ) { }
    
        inline void Put(
        	Arg< std::string >::Type key,
            Arg< JsonBase::Ref >::Type value )
            { mDictionary[ key ] = value; }
    
        virtual JsonBase::Ref GetValueForKey( Arg< std::string >::Type key )
        {
            JsonBase::Ref refJson = mDictionary[ key ];
            
            if ( ! refJson.isValid() )
            {
                return new JsonNull();
            }
            
            return refJson;
        }
    
        virtual void SetValueForKey(
        	Arg< std::string >::Type key,
            Arg< JsonBase::Ref >::Type jsonRef )
        {
            mDictionary.insert(std::make_pair(key,jsonRef));
        }
    
    	virtual void SetIntegerValueForKey(
        	Arg< std::string >::Type key,
            Arg< JsonIntType >::Type intValue )
    	{
        	SetValueForKey( key, new JsonInteger( intValue ) );
        }
    
        virtual void SetStringValueForKey(
        	Arg< std::string >::Type key,
            Arg< std::string >::Type value )
    	{
        	SetValueForKey( key, new JsonString( value ) );
        }
    
        virtual const std::string Dump( JsonIntType indentAmount )
        {
            std::string s = Sl( "{\n" );
            
            for(auto&& pair: mDictionary)
            {
                s += indent( indentAmount + 1 ) + pair.first;
                s += Sl( " : " );
                s += pair.second->Dump( indentAmount + 2 );
                s += Sl( "\n" );
            }
            
            s += Sl( "\n" ) + indent( indentAmount ) + Sl( "}" );
            
            return s;
        }
    
        virtual const std::string Stringify( ) const
    	{
           	std::string s = Sl( "{" );
            
            bool first = true;
            for(auto&& pair : mDictionary)
            {
            	if (first)
            	{
                    first = false;
                	s += Sl( "," );
            	}
                
                s += Sl( "\"" ) + pair.first + Sl( "\"" );
                s += Sl( ":" );
                s += pair.second->Stringify();
            }
            
            s += Sl( "}" );
            
            return s;
    	}
    
    private:
    
        DictType mDictionary;
};

class JsonArray : public JsonBase
{
    public:
    
        inline JsonArray( void ) : JsonBase( Type::Array ) { }

        inline void PushBack( Arg< JsonBase::Ref >::Type refJson )
        {
            mVector.push_back( refJson );
        }
    
        virtual const std::string Dump( JsonIntType indentAmount )
        {
            std::string s = Sl( "\n" ) + indent( indentAmount ) + Fs( "[ (%d)\n", mVector.size() );
            
            for(size_t i = 0; i < mVector.size(); i ++ )
            {
                s += indent( indentAmount + 1 ) + Fs( "%d. ", i ) + mVector[ i ]->Dump( indentAmount + 2 ) + Sl( "\n" );
            }
            
            s += indent( indentAmount ) + Sl( "]" );
            
            return s;
        }
    
        virtual const std::string Stringify( ) const
    	{
          	std::string s = Sl( "[" );
            
            for(size_t i = 0; i < mVector.size(); i ++ )
            {
            	if ( i > 0 )
            	{
                	s += Sl( "," );
            	}
                
                s += mVector[ i ]->Stringify( );
            }
            
            s += Sl( "]" );
            
            return s;
        }
    
        virtual JsonIntType GetCount( void )
        {
            return mVector.size();
        }
    
        virtual JsonBase::Ref GetAt( JsonIntType i )
        {
            return mVector[i];
        }
    
    private:
    
        std::vector< JsonBase::Ref > mVector;
};

class Json
{
    public:
    
        Json( JsonBase::Ref refJson )
        {
            ASSERT( refJson.isValid() );

            mrefJson = refJson;
        }
    
        Json( Arg< std::string >::Type string )
        {
            mrefJson = new JsonString( string );
        }
    
        Json( Arg< JsonIntType >::Type integer )
    	{
        	mrefJson = new JsonInteger( integer );
        }
    
        Json( )
        {
            mrefJson = new JsonNull();
        }
    
        inline void PushBack( Json json )
        {
        	mrefJson->push_back( json.mrefJson );
    	}
    
        inline const Json GetAt( JsonIntType i ) const
        {
            return Json( mrefJson->GetAt( i ) );
        }
        
        inline JsonIntType GetCount( void ) const
        {
            return mrefJson->GetCount();
        }
    
        inline const std::string Dump( JsonIntType indent ) const
        {
            return mrefJson->Dump( indent );
        }
    
    	inline const std::string Stringify( ) const
    	{
        	return mrefJson->Stringify();
        }
    
        inline const Json GetValueForKey( Arg< std::string >::Type json ) const
        {
            return Json( mrefJson->GetValueForKey( json ) );
        }
    
        inline const void SetValueForKey(
            Arg< std::string >::Type key,
            Arg< Json >::Type json )
        {
            mrefJson->SetValueForKey( key, json.mrefJson );
        }
    
    	inline void SetIntegerValueForKey(
        	Arg< std::string >::Type key,
            Arg< JsonIntType >::Type intValue )
    	{
        	SetValueForKey( key, Json( new JsonInteger( intValue ) ) );
        }
    
        inline void SetStringValueForKey(
        	Arg< std::string >::Type key,
            Arg< std::string >::Type value )
    	{
        	SetValueForKey( key, Json( new JsonString( value ) ) );
        }
    
        inline const std::string GetString( void ) const
        {
            return mrefJson->GetString();
        }
    
        inline const JsonFloatType GetFloat64( void ) const
        {
            return mrefJson->GetFloat64();
        }
    
        inline const JsonIntType GetUInt( void ) const
        {
            return mrefJson->GetUInt();
        }
    
        inline const bool GetBool( void ) const
        {
            return mrefJson->GetBool();
        }
    
        inline bool IsNull( void ) const
        {
        	return JsonBase::Type::Null == mrefJson->GetType();
    	}
    
        inline const Json operator[] ( const char* pChar ) const
        {
            return Json( mrefJson->GetValueForKey( Ts( pChar ) ) );
        }
        
        inline const Json operator[] ( Arg< std::string >::Type s ) const
        {
            return Json( mrefJson->GetValueForKey( s ) );
        }
    
        inline const Json operator[] ( JsonIntType i ) const
        {
            return Json( mrefJson->GetAt( i ) );
        }

        inline bool operator==( Arg< std::string >::Type s ) const
        {
            return mrefJson->GetString() == s;
        }
    
        inline bool operator==( const char* pCString ) const
        {
            return mrefJson->GetString() == Ts( pCString );
        }

    
    private:
    
        JsonBase::Ref mrefJson;
};
