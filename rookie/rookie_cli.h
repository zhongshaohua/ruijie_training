/* _ROOKIE_CLI_H_ */
// #ifndef _ROOKIE_CLI_H_
// #define _ROOKIE_CLI_H_

// void exec_rookie_cmd(struct_command_data_block *pcdb);

// EOLWOS(exec_rookie_eol, exec_rookie_cmd);
/* 匹配关键字rookie */
// KEYWORD(exec_rookie, exec_rookie_eol, ALTERNATE, "rookie", "rookie", PRIVILEGE_USER);

// #undef ALTERNATE
// #define ALTENATE exec_rookie

// #endif  /* _ROOKIE_CLI_H_ */



// APPEND_HERE(show_command_extend_here, no_alt);
// /*声明执行函数*/
// void exec_show_rookie_route_cmd(struct_command_data_block *pcdb);
// void exec_show_rookie_route_count_cmd(struct_command_data_block *pcdb);

// /*声明命令结束*/
// EOLWS_K(exec_show_rookie_route_eol, exec_show_ip_route_cmd);
// EOLWS_K(exec_show_rookie_route_count_eol, exec_show_ip_route_cmd);

// /*匹配关键字"rookie"*/
// KEYWORD(exec_show_rookie,exec_show_rookie_route,ALTERNATE, \
//          "rookie","incomplete ",PRIVILEGE_USER)
// /*匹配关键字"count"*/
// KEYWORD(exec_show_rookie_route_count,exec_show_rookie_route_count_eol,exec_show_rookie_route_eol, \
//          "count","The count of route",PRIVILEGE_USER)
// /*匹配关键字"route"*/
// KEYWORD(exec_show_rookie_route,exec_show_rookie_route_count,ALTERNATE, \
//          "route","IP routing table",PRIVILEGE_USER)

// #undef ALTERNATE
// #define ALTERNATE exec_show_rookie_route



void exec_rookie_route_add_cmd(struct_command_data_block *pcdb);
void exec_rookie_route_algorithm_cmd(struct_command_data_block *pcdb);
void exec_rookie_route_agetime_cmd(struct_command_data_block *pcdb);
/*声明命令结束*/
EOLWOS(exec_rookie_route_add_eol,exec_rookie_route_add_cmd);
EOLWOS(exec_rookie_route_algorithm_str_eol,exec_rookie_route_algorithm_cmd);
EOLWOS(exec_rookie_route_agetime_in_eol,exec_rookie_route_agetime_cmd);


/*匹配关键字"age-time"*/
NUM_DEC(exec_rookie_route_agetime_in,exec_rookie_route_agetime_in_eol,no_alt,"age-time (default 10)",CDBVAR(int,1),1,1000);
/*匹配关键字"algorithm hash or lpm"*/
TXT_LINE(exec_rookie_route_algorithm_str,exec_rookie_route_algorithm_str_eol,no_alt, \
         "The algorithm of FIB",CDBVAR(string,1));
/*匹配关键字"age"*/
KEYWORD(exec_rookie_route_agetime,exec_rookie_route_agetime_in,no_alt, \
         "age-time","rookie route age-time",PRIVILEGE_USER);
/*匹配关键字"algorithm"*/
KEYWORD(exec_rookie_route_algorithm,exec_rookie_route_algorithm_str,exec_rookie_route_agetime, \
         "algorithm","rookie route algorithm",PRIVILEGE_USER);
IPADDR(exec_rookie_route_add_ip_mask_ip,exec_rookie_route_add_eol,no_alt, \
       "Network mask",CDBVAR(paddr,3));
IPMASK(exec_rookie_route_add_ip_mask,exec_rookie_route_add_ip_mask_ip,no_alt, \
       "nexthop",CDBVAR(paddr,2));
IPADDR(exec_rookie_route_add_ip,exec_rookie_route_add_ip_mask,no_alt, \
       "dstip",CDBVAR(paddr,1));
/*匹配关键字"add"*/
KEYWORD(exec_rookie_route_add,exec_rookie_route_add_ip,exec_rookie_route_algorithm,"add","rookie route add",PRIVILEGE_USER);
/*匹配关键字"route"*/
KEYWORD(exec_rookie_route,exec_rookie_route_add,no_alt, "route","route",PRIVILEGE_USER);
/*匹配关键字"rookie"*/
KEYWORD(exec_rookie,exec_rookie_route,ALTERNATE,"rookie","rookie",PRIVILEGE_USER);

#undef ALTERNATE
#define ALTERNATE exec_rookie