#ifndef TABLE2_INCLUDED
#define TABLE2_INCLUDED

#include <cstdint>
#include <limits>
#include <exception>
#include <stdexcept>  // std::runtime_error

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 2-bit depth map.
 */
class Table2 {
public:
  /*!
   * @brief Contructor
   */
  Table2();

  /*!
   * @brief Contructor
   * @param[in] width          Map width.
   * @param[in] height         Map height.
   * @param[in] default_value  Default fill value. (0 - 3)
   * @exception std::runtime_error  Parameter error.
   */
  Table2(const int width, const int height, const int default_value = 0);

  /*!
   * @brief Contructor
   * @param[in] tmp  Copy source.
   */
  Table2(const Table2& tmp);

  /*!
   * @brief Destructor
   */
  ~Table2();

  /*!
   * @brief Clear map.
   * @param[in] value  Fill value. (0 - 3)
   * @exception std::runtime_error  Parameter error.
   * @details
   * Fill map by specified value.
   */
  void Clear(const int value = 0);

  /*!
   * @brief Setter
   * @param[in] x      X position.
   * @param[in] y      Y position.
   * @param[in] value  Set value. (0 - 3)
   * @exception std::runtime_error  Parameter error.
   * @details
   * Set value.
   */
  void Set(const int x, const int y, const int value);

  /*!
   * @brief Getter
   * @param[in] x                   X position.
   * @param[in] y                   Y position.
   * @param[in] out_of_range_value  Out of range value. (0 - 3)
   * @return Value of specified position. (0 - 3)
   * @details
   * Get value.
   * If out of range, return out_of_range_value.
   */
  int Get(const int x, const int y, const int out_of_range_value = 0) const;

  /*!
   * @brief Get map width.
   * @return Map width.
   * @details
   * Get map width.
   */
  int Width() const;

  /*!
   * @brief Get map height.
   * @return Map height.
   * @details
   * Get map height.
   */
  int Height() const;

  /*!
   * @brief Selectable clear map.
   * @param[in] src  Before value. (0 - 3)
   * @param[in] dst  After value. (0 - 3)
   * @exception std::runtime_error  Parameter error.
   * @details
   * Find src value and replace to dst value.
   */
  void Replace(const int src, const int dst);

  /*!
   * @brief Get hash value.
   * @return Hash value.
   * @details
   * Calculate hash value.
   */
  std::size_t Hash() const;

  /*!
   * @brief = operator.
   * @param[in] tmp  Copy source.
   * @details
   * Copy from source.
   */
  Table2& operator = (const Table2& tmp);

  /*!
   * @brief = operator.
   * @param[in] tmp  Compare source.
   * @retval true  Same
   * @retval false Not same
   * @details
   * Compare source.
   */
  bool Equal(const Table2& tmp) const;

//protected:
  int8_t   width_;   //!< Map width.
  int8_t   height_;  //!< Map height.
  int16_t  size_;
  uint8_t* data_;    //!< Map data.
};

///////////////////////////////////////////////////////////////////////////////
inline bool operator == (const Table2& a, const Table2& b) {
  return a.Equal(b);
}

///////////////////////////////////////////////////////////////////////////////
namespace std {

template<>
class hash<Table2> {
public:
  std::size_t operator()(const Table2& table) const {
    return table.Hash();
  }
};

template<>
class hash<Table2*> {
public:
  std::size_t operator()(const Table2* table) const {
    return table->Hash();
  }
};

}  // std

#endif  // TABLE2_INCLUDED
