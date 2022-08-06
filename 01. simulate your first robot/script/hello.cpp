// Include the headers
#include <iostream>
#include <gazebo/gazebo.hh>

// Gazebo namespace
namespace gazebo {

    // Class for plugin which inherits from WorldPlugin inside gazebo
    class WorldPluginMyRobot : public WorldPlugin {

        // Constructor function
        public: WorldPluginMyRobot() : WorldPlugin() {

            // Print hello world
            printf("Hello World! \n");

        }

        // Load function for recieving info from world (mandetory)
        public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) {

        }

    };

    // Register the plugin class in the simulator
    GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot);

}