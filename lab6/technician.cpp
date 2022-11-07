#include <iostream>
#include "technician.h"
#include "computer.h"
#include "electronics.h"

const int MAX_NUM_TECHNICIAN = 10;

// TODO: initialize the static varibles of class Technician
int Technician:: num_technician{ 0 };
Technician* Technician:: technician_list[ MAX_NUM_TECHNICIAN ] { NULL };

// TODO: Implement the constructor
Technician::Technician(std::string name, Diagnosis_Tool* diagnosis_tool) : 
name( name ),
diagnosis_tool( diagnosis_tool ),
num_order_finished( 0 )
{
    technician_list[ num_technician ] = this;
    num_technician += 1;
}

Technician::~Technician(){
    delete diagnosis_tool;
}

CPU* Technician::acquire_CPU(CPU_Model model) const {
    return new CPU(model);
}

MEM* Technician::acquire_MEM(MEM_Model model) const {
    return new MEM(model);
}

// TODO: implement repair function
void Technician::repair(Computer* computer){
    if ( ! this->diagnosis_tool->diagnose( computer->cpu ) )
    {
        CPU:: defect_count += 1;
        CPU_Model cpu_model = this->diagnosis_tool->get_CPU_Model( computer->cpu );
        delete computer->cpu;
        computer->cpu = this->acquire_CPU( cpu_model );
    }

    if ( ! this->diagnosis_tool->diagnose( computer->mem ) )
    {
        MEM :: defect_count += 1;
        MEM_Model mem_model = this->diagnosis_tool->get_MEM_Model( computer->mem );
        delete computer->mem;
        computer->mem = this->acquire_MEM( mem_model );
    }
    this->num_order_finished += 1;
}

void Technician::print_report(){
    std::cout << "----------------------" << std::endl;
    std::cout << "REPORT FOR TECHNICIANS" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout.width(20);
    std::cout << std::left << "NAME" << "ORDERS_COMPLETED" << std::endl;
    for(int i = 0; i < num_technician; ++i){
        std::cout.width(20);
        std::cout << std::left << technician_list[i]->name << technician_list[i]->num_order_finished << std::endl;
    }
}
