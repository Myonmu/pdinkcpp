#pragma once

#include "emitter.h"
#include "binary_stream.h"

namespace ink::compiler::internal
{
	struct container_data;

	// binary emitter
	class binary_emitter : public emitter
	{
	public:
		binary_emitter();
		virtual ~binary_emitter();

		// Begin emitter
		virtual uint32_t start_container(int index_in_parent, const std::string& name) override;
		virtual uint32_t end_container() override;
		virtual void write_raw(Command command, CommandFlag flag = CommandFlag::NO_FLAGS, const char* payload = nullptr, ink::size_t payload_size = 0) override;
		virtual void write_path(Command command, CommandFlag flag, const std::string& path, bool useCountIndex = false) override;
		virtual void write_variable(Command command, CommandFlag flag, const std::string& name) override;
		virtual void write_string(Command command, CommandFlag flag, const std::string& string) override;
		virtual void handle_nop(int index_in_parent) override;
		virtual uint32_t fallthrough_divert() override;
		virtual void patch_fallthroughs(uint32_t position) override;
		// End emitter

		// write out the emitters data
		virtual void output(std::ostream&);

	protected:
		virtual void initialize() override;
		virtual void finalize() override;

	private:
		void process_paths();
		void write_container_map(std::ostream&, const container_map&, container_t);
		void write_container_hash_map(std::ostream&);
		void write_container_hash_map(std::ostream&, const std::string&, const container_data*);

	private:
		container_data* _root;
		container_data* _current;
		compilation_results* _results;

		binary_stream _strings;
		binary_stream _containers;

		std::vector<std::tuple<size_t, std::string, container_data*, bool>> _paths;
	};
}