#ifndef __CPCA15_USER_INFO_H__
#define __CPCA15_USER_INFO_H__
#include<SecureBuffer.h>
#include<string>
#include<set>
#include<vector>

#define UR_DISP_ERROR 0
#define UR_DISP_ISSUED 1
#define UR_DISP_UNDER_SUBMISSION 2

class CPCA15UserField
{
    public:
	std::string form_name;
	std::string name;
	std::string value;
	bool mandatory;
	bool is_separator;
	long maxlen;
	std::set<std::string> allowed_values;
	CPCA15UserField() : form_name(),name(),value(),mandatory(false),
			is_separator(false),maxlen(-1),allowed_values()
	{
	};

	CPCA15UserField(const CPCA15UserField & f) : 
		form_name(f.form_name),
		name(f.name),value(f.value),
		mandatory(f.mandatory),		
		is_separator(f.is_separator),
		maxlen(f.maxlen),
		allowed_values(f.allowed_values)
	{
	};

	bool valid() const
	{
	    if ( maxlen>0 && (long)value.length() > maxlen )
		return false;
	    if ( value.empty() && mandatory )
		return false;
	    if ( !allowed_values.empty() && 
		    value.size() > 0 &&
		    allowed_values.find(value) == allowed_values.end() )
		return false;
	    return true;
	};
	bool parse(const std::string & cell);
	std::string post_string() const;
};

typedef std::vector<CPCA15UserField> CPCA15UserFields;

class CPCA15UserInfo
{
    static const unsigned int c_magic = 0xDeda1001;
    unsigned int magic;
    public:
	CPCA15UserFields fields;
	std::string TokenID;
	CSecurePin * sbPassword;
	unsigned int status;

	CPCA15UserInfo() : magic(c_magic), fields(), TokenID(), 
	    sbPassword(0), status(UR_DISP_ERROR)
	{
	};

	bool parse_response(const std::string & html);
	bool parse(const std::string & html);
	
	bool check_field_name(std::string fname)
	{
	    for(CPCA15UserFields::iterator it = fields.begin(); 
			    it != fields.end(); ++it)
	    {
		if(it->form_name == fname)
		return true;
	    }
	    return false;
	}
	
	std::string & operator [](std::string fname)
	{
	    for(CPCA15UserFields::iterator it = fields.begin(); 
		it != fields.end(); ++it)
	    {
		if(it->form_name == fname)
		  return it->value;
	    }
	    return fields.begin()->value;
	}

	bool corrupted()
	{
	    return magic != c_magic;
	};
	bool valid() 
	{
	    for (CPCA15UserFields::iterator it = fields.begin();
		it != fields.end(); it++)
	    {
		if ( ! it->valid() )
		    return false;
	    }
	    return true;
	}
	
	int get_first_bad_field()
        {
	
	    for (size_t i = 0; i < fields.size(); ++i)
	    {
		if ( ! fields[i].valid() )
		    return (int)i;
	    }
	    return -1;
	}

	std::string post_string() const;
	~CPCA15UserInfo()
	{
	    if (!corrupted() && sbPassword)
		delete sbPassword;
	};
};

#endif

