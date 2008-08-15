#ifndef OPENMM_BROOK_STREAM_INTERNAL_H_
#define OPENMM_BROOK_STREAM_INTERNAL_H_

/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright ( c ) 2008 Stanford University and the Authors.           *
 * Authors: Peter Eastman, Mark Friedrichs                                    *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files ( the "Software" ), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include <brook/brook.hpp>
#include "SimTKUtilities/SimTKOpenMMRealType.h"

namespace OpenMM {

/**
 * This is the implementation of Float and Double streams in the Brook Platform.
 */

class BrookStreamInternal {

   public:

      /** 
        * This is an enumeration of the allowed data types for a Stream.
        */
      enum DataType { Float, Float2, Float3, Float4, Double, Double2, Double3, Double4, Integer, Integer2, Integer3, Integer4, Unknown };

      /**
       * BrookStreamInternal constructor
       * 
       * @param name        name of the stream to create
       * @param size        number of elements in the stream
       * @param streamWidth stream width
       * @param type        data type of each element in the stream
       *
       */
  
      BrookStreamInternal( const std::string& name, int size, int streamWidth, BrookStreamInternal::DataType type );
  
      /**
       * BrookStreamInternal destructor
       * 
       */

      ~BrookStreamInternal( );
  
      /**
       * Get the name of this stream.
       */
  
      const std::string& getName( void ) const;
  
      /**
       * Get the number of elements in this stream.
       */
  
      int getSize( void ) const;
  
      /**
       * Get the data type of each element in the stream.
       */
  
      BrookStreamInternal::DataType getDataType( void ) const;
  
      /**
       * Get base data type of each element in the stream ( float, double, int )
       */
  
      BrookStreamInternal::DataType getBaseDataType( void ) const;
  
      /**
       * Copy the contents of an array into this stream.
       * 
       * @param  array a pointer to the start of the array.  The array is assumed to have the same length as this stream,
       * and to contain elements of the correct data type for this stream.  If the stream has a compound data type, all
       * the values should be packed into a single array: all the values for the first element, followed by all the values
       * for the next element, etc.
       */
      virtual void loadFromArray(const void* array) = 0;
  
      /**
       * Copy the contents of an array into this stream.
       * 
       * @param  array a pointer to the start of the array.  The array is assumed to have the same length as this stream,
       * and to contain elements of the correct data type for this stream.  If the stream has a compound data type, all
       * the values should be packed into a single array: all the values for the first element, followed by all the values
       * for the next element, etc.
       */
      virtual void loadFromArray( const void* array, BrookStreamInternal::DataType baseType ) = 0;
  
      /**
       * Copy the contents of this stream into an array.
       * 
       * @param  array a pointer to the start of the array.  The array is assumed to have the same length as this stream,
       * and to contain elements of the correct data type for this stream.  If the stream has a compound data type, all
       * the values should be packed into a single array: all the values for the first element, followed by all the values
       * for the next element, etc.
       */
      virtual void saveToArray(void* array) = 0;
  
      /**
       * Set every element of this stream to the same value.
       * 
       * @param a pointer to the value.  It is assumed to be of the correct data type for this stream.
       */
      virtual void fillWithValue(void* value) = 0;
  
      /**
       * Get data
       * 
       * @return data array
       */
      virtual void* getData( void ) = 0;
  
      /** 
       * Get type string
       *
       * @param type        BrookStreamInternal data type (float, float2, ...)
       *
       * @return string matching type or "Unknown"
       * 
       */
      
      std::string getTypeString( BrookStreamInternal::DataType type ) const;
      
      /** 
       * Get Brook stream reference
       * 
       * @return  Brook stream reference
       */
      
      brook::stream& getBrookStream( void );

      /** 
       * Get width
       * 
       * @return width
       */

      int getWidth( void ) const;
    
      /** 
       * Get stream width
       * 
       * @return stream width
       */

      int getStreamWidth( void ) const;

      /** 
       * Get stream height
       * 
       * @return stream height
       */

      int getStreamHeight( void ) const;

      /** 
       * Get stream size
       * 
       * @return stream size
       */

      int getStreamSize( void ) const;

      /* 
       * Get contents of object
       *
       *
       * @param level   level of dump
       *
       * @return string containing contents
       *
       * */

      const std::string getContentsString( int level = 0 ) const;

   protected:

      std::string _name;

      BrookStreamInternal::DataType _type;
      BrookStreamInternal::DataType _baseType;

      int _size;
      int _width;
      int _streamWidth;
      int _streamHeight;
      int _streamSize;
  
      brook::stream _aStream;
  
      /* 
       * Get contents of object
       *
       * @param tab         tab
       * @param description description
       * @param value       value
       *
       * @return string containing contents
       *
       * */
      
      std::string _getLine( const std::string& tab, const std::string& description, 
                            const std::string& value ) const;
      
};

} // namespace OpenMM

#endif /* OPENMM_BROOK_STREAM_INTERNAL_H_ */
