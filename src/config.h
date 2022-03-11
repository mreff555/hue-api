#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <cstdint>

#define DEFAULT_CONFIG_FILE ".config.json"

class Config 
{
  public:
  Config();

  virtual ~Config();

  /**
   * @brief Reads default config file into memory, replacing original contents
   * @param N/A
   * Return N/A
   */
  void read();
  
  /**
   * @brief Reads specified config file into memory, replacing original contents
   * @param N/A
   * Return N/A
   */
  void read(std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  void write();

  /**
   * @brief 
   * @param
   * Return
   */
  void write(std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  std::string getId() const;

  /**
   * @brief 
   * @param
   * Return
   */
  void setId(const std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  std::string getInternalIpAddress() const;

  /**
   * @brief 
   * @param
   * Return
   */
  void setInternalIpAddress(const std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  std::string getUsername() const;

  /**
   * @brief 
   * @param
   * Return
   */
  void setUsername(const std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  std::string getPassword() const;

  /**
   * @brief 
   * @param
   * Return
   */
  void setPassword(const std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  std::string getUrl() const;

  /**
   * @brief 
   * @param
   * Return
   */
  void setUrl(const std::string);

  /**
   * @brief 
   * @param
   * Return
   */
  uint64_t getTimestamp() const;

  private:

  std::string id;

  std::string internalIpAddress;

  std::string username;

  std::string password;

  std::string url;

  uint64_t timestamp;

};


#endif /* CONFIG_H */
