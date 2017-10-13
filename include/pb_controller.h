#ifndef PODBOAT_CONTROLLER_H_
#define PODBOAT_CONTROLLER_H_

#include <string>
#include <configcontainer.h>
#include <download.h>
#include <queueloader.h>
#include <vector>

namespace podboat {

class pb_view;

class queueloader;

class pb_controller {
	public:
		pb_controller();
		~pb_controller();
		inline void set_view(pb_view * vv) {
			v = vv;
		}
		int run(int argc, char * argv[] = 0);

		inline bool view_update_necessary() const {
			return view_update_;
		}
		inline void set_view_update_necessary(bool b) {
			view_update_ = b;
		}
		std::vector<download>& downloads() {
			return downloads_;
		}

		int usage(const char * argv0);

		std::string get_dlpath();

		unsigned int downloads_in_progress();
		void reload_queue(bool remove_unplayed = false);

		unsigned int get_maxdownloads();
		void start_downloads();

		void increase_parallel_downloads();
		void decrease_parallel_downloads();

		double get_total_kbps();

		void play_file(const std::string& str);

		inline newsboat::configcontainer * get_cfgcont() {
			return cfg;
		}

	private:
		bool setup_dirs_xdg(const char *env_home);

		pb_view * v;
		std::string config_file;
		std::string queue_file;
		newsboat::configcontainer * cfg;
		bool view_update_;
		std::vector<download> downloads_;

		std::string config_dir;
		std::string url_file;
		std::string cache_file;
		std::string searchfile;
		std::string cmdlinefile;

		unsigned int max_dls;

		queueloader * ql;
};

}

#endif /* PODBOAT_CONTROLLER_H_ */
