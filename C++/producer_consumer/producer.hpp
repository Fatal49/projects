#ifndef _PRODUCER_HPP_
#define _PRODUCER_HPP_

#include "headers.hpp"
#include "product.hpp"

class Producer : public std::exception {
public:
    
    // Constructor
    explicit Producer(const std::string& companyName) : CompanyName(companyName) {}
    explicit Producer(const std::string& companyName, std::vector<Product*> pcontainer) 
        : CompanyName(companyName), ProductContainer(pcontainer) {}

    // Deleted constructors and methods
    Producer(const std::string&, std::vector<Product*>&&) = delete;

    // Getters
    std::size_t GetCompanyID() const;


private:

    // Private methods
    void GenID(std::size_t& _id);

    // Deleted private methods
    void GenID(std::size_t&&) = delete;

    std::string CompanyName;
    std::vector<Product*> ProductContainer;
    std::size_t CompanyId;
};

#endif /* _PRODUCER_HPP_ */
