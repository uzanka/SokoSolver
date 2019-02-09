#ifndef TABLES_INCLUDED
#define TABLES_INCLUDED

#include <cstdint>
#include <exception>
#include <limits>
#include <stdexcept>  // std::runtime_error
#include <string>

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 8-bit depth map.
 */
class TableS {
public:
  /*!
   * @brief Contructor
   */
  TableS();

  /*!
   * @brief Contructor
   * @param[in] width          Map width.
   * @param[in] height         Map height.
   * @param[in] default_value  Default fill value. (0 - 127)
   * @exception std::runtime_error  Parameter error.
   */
  TableS(const int width, const int height, const int default_value = ' ');

  /*!
   * @brief Destructor
   */
  ~TableS();

  /*!
   * @brief Clear map.
   * @param[in] value  Fill value. (0 - 127)
   * @exception std::runtime_error  Parameter error.
   * @details
   * Fill map by specified value.
   */
  void Clear(const int value = ' ');

  /*!
   * @brief Setter
   * @param[in] x      X position.
   * @param[in] y      Y position.
   * @param[in] value  Set value. (0 - 127)
   * @exception std::runtime_error  Parameter error.
   * @details
   * Set value.
   */
  void Set(const int x, const int y, const int value);

  /*!
   * @brief Getter
   * @param[in] x                   X position.
   * @param[in] y                   Y position.
   * @param[in] out_of_range_value  Out of range value. (0 - 127)
   * @return Value of specified position. (0 - 127)
   * @details
   * Get value.
   * If out of range, return out_of_range_value.
   */
  int Get(const int x, const int y, const int out_of_range_value = ' ') const;

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

//protected:
  std::string data_;  //!< Map data.
};

///////////////////////////////////////////////////////////////////////////////
inline bool operator == (const TableS& a, const TableS& b) {
  return a.data_ == b.data_;
}

///////////////////////////////////////////////////////////////////////////////
namespace std {

template<>
class hash<TableS> {
public:
  std::size_t operator()(const TableS& table) const {
    return table.Hash();
  }
};

template<>
class hash<TableS*> {
public:
  std::size_t operator()(const TableS* table) const {
    return table->Hash();
  }
};

}  // std

#endif  // TABLES_INCLUDED
