<?php
/*
    extended-gui_create_config2.inc

    Copyright (c) 2014 - 2016 Andreas Schmidhuber
    All rights reserved.

	Portions of NAS4Free (http://www.nas4free.org).
	Copyright (c) 2012-2016 The NAS4Free Project <info@nas4free.org>.
	All rights reserved.

	Portions of freenas (http://www.freenas.org).
	Copyright (c) 2005-2011 by Olivier Cochard <olivier@freenas.org>.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	The views and conclusions contained in the software and documentation are those
	of the authors and should not be interpreted as representing official policies,
	either expressed or implied, of the NAS4Free Project.
*/

if (is_array($config['extended-gui']['shares'])) unset($config['extended-gui']['shares']);              // reset shares array
$config['extended-gui']['shares'] = array();
$raid_variants = array('gmirror', 'graid5', 'gconcat', 'gvinum', 'gstripe');                            // set supported raid variants
$eguiconfig = fopen("/var/scripts/CONFIG2", "w");                                                       // create disk/share config file
    $clogdir = rc_getenv_ex("clog_logdir", $g['varlog_path']);                                          // get logdir from environment and
    fwrite($eguiconfig, "SYSTEM_LOG_DIR={$clogdir}"."\n");                                              // write it to CONFIG2
    $txt = isset($config['samba']['enable']) ? "1" : "0";                                               // for user_check script
    fwrite($eguiconfig, "SMB_ENABLED=".$txt."\n");
    $txt = isset($config['ftpd']['enable']) ? "1" : "0";                                                // for user_check script
    fwrite($eguiconfig, "FTP_ENABLED=".$txt."\n");
    $txt = isset($config['extended-gui']['beep']) ? "1" : "0";                                          // for beep script
    fwrite($eguiconfig, "RUN_BEEP=".$txt."\n");
    $txt = isset($config['extended-gui']['boot']) ? "1" : "0";                                          // for disk_check.sh script
    fwrite($eguiconfig, "OS_FS=A_OS"."\n");
    $txt = isset($config['extended-gui']['varfs']) ? "1" : "0";                                         // for disk_check.sh script
    fwrite($eguiconfig, "VAR_FS=A_VAR"."\n");
    $txt = isset($config['extended-gui']['usrfs']) ? "1" : "0";                                         // for disk_check.sh script
    fwrite($eguiconfig, "USR_FS=A_USR"."\n");
    $txt = isset($config['extended-gui']['temp_always']) ? "1" : "0";                                   // for disk_check.sh script
    fwrite($eguiconfig, "TEMP_ALWAYS=".$txt."\n");
    $txt = system_get_cpus();                                                                           // for cpu_check.sh script
    fwrite($eguiconfig, "CPU_NUMBER='{$txt}'"."\n");       
    fwrite($eguiconfig, "CPU_TEMP_WARNING='{$config['extended-gui']['cpu_temp_warning']}'"."\n");
    fwrite($eguiconfig, "CPU_TEMP_SEVERE='{$config['extended-gui']['cpu_temp_severe']}'"."\n");
    fwrite($eguiconfig, "CPU_TEMP_HYSTERESIS='{$config['extended-gui']['cpu_temp_hysteresis']}'"."\n");
    $txt = isset($config['extended-gui']['cpu_temp_email']) ? "1" : "0";
    fwrite($eguiconfig, "EMAIL_CPU_TEMP_ENABLED=".$txt."\n");
    fwrite($eguiconfig, "TEMP_WARNING='{$config['extended-gui']['temp_warning']}'"."\n");               // for disk_check.sh script
    fwrite($eguiconfig, "TEMP_SEVERE='{$config['extended-gui']['temp_severe']}'"."\n");
    fwrite($eguiconfig, "SPACE_WARNING_MB='{$config['extended-gui']['space_warning']}'"."\n");          // for disk_check.sh script
    fwrite($eguiconfig, "SPACE_WARNING_PC='{$config['extended-gui']['space_warning_percent']}'"."\n");
    fwrite($eguiconfig, "SPACE_SEVERE_MB='{$config['extended-gui']['space_severe']}'"."\n");
    fwrite($eguiconfig, "SPACE_SEVERE_PC='{$config['extended-gui']['space_severe_percent']}'"."\n");
    $txt = isset($config['extended-gui']['space_email']) ? "1" : "0";
    fwrite($eguiconfig, "EMAIL_SPACE_ENABLED=".$txt."\n");
    $txt = isset($config['extended-gui']['zfs_degraded_email']) ? "1" : "0";
    fwrite($eguiconfig, "EMAIL_DEGRADED_ENABLED=".$txt."\n");
    fwrite($eguiconfig, "EMAIL_TO='{$config['extended-gui']['space_email_add']}'"."\n");
    fwrite($eguiconfig, "EMAIL_FROM='{$config['system']['email']['from']}'"."\n");                      // for email.sh script
    $txt = isset($config['extended-gui']['user']) ? "1" : "0";                                          // for extended-gui_system_calls.sh script
    fwrite($eguiconfig, "RUN_USER=".$txt."\n");
    $txt = isset($config['extended-gui']['hosts']) ? "1" : "0";
    fwrite($eguiconfig, "RUN_HOSTS=".$txt."\n");
    $txt = isset($config['extended-gui']['automount']) ? "1" : "0";
    fwrite($eguiconfig, "RUN_AUTOMOUNT=".$txt."\n");
    if ($g['platform'] == "full") fwrite($eguiconfig, "FIRST_USB='0'"."\n");                            // for automount.sh script
    else fwrite($eguiconfig, "FIRST_USB='1'"."\n");
    fwrite($eguiconfig, "LOOP_DELAY='{$config['extended-gui']['loop_delay']}'"."\n");
    fwrite($eguiconfig, "SUBNET='{$config['extended-gui']['hosts_network']}'"."\n");                    // for hosts_check.sh script
    fwrite($eguiconfig, "START_IP='{$config['extended-gui']['hosts_network_start']}'"."\n");
    fwrite($eguiconfig, "END_IP='{$config['extended-gui']['hosts_network_end']}'"."\n");
    fwrite($eguiconfig, "DAYSOLD='{$config['extended-gui']['purge']['days']}'"."\n");                    // for purge.sh script
    $txt = isset($config['extended-gui']['user_email']) ? "1" : "0";                                     // for user_check.sh script
    fwrite($eguiconfig, "EMAIL_ENABLED=".$txt."\n");

    // get all mountpoints + pools including all disks for eGUI index.php
    $i = 0;                                                                                             // set to initialize if there are no mounts
    if (is_array($config['mounts']) && is_array($config['mounts']['mount'])) {
        for ($i = 0; $i < count($config['mounts']['mount']); ++$i) {
            $is_raid = 0;                                                                               // set to check if this is a raid
            fwrite($eguiconfig, "MOUNT{$i}={$config['mounts']['mount'][$i]['sharename']}"."\n");        // get sharenames
            foreach($raid_variants as $rv) {                                                            // check raid variants
                if (is_array($config[$rv]) && is_array($config[$rv]['vdisk'])) {
                    for ($k = 0; $k < count($config[$rv]['vdisk']); ++$k) {                             // get vdevice
                		if (preg_match("[{$config['mounts']['mount'][$i]['mdisk']}]", $config[$rv]['vdisk'][$k]['devicespecialfile'])) {
                            $is_raid = 1;
                            for ($l = 0; $l < count($config[$rv]['vdisk'][$k]['device']); ++$l) {
                                $device_raw = explode(".", str_replace("/dev/", "", $config[$rv]['vdisk'][$k]['device'][$l]));    // get rid of .eli .nop etc and /dev/
                                fwrite($eguiconfig, "MOUNT{$i}DISK{$l}={$device_raw[0]}"."\n");         // get vdevice disks
                            }
                        }
                    }
                }
            }
            if ($is_raid == 0) {
                $device_raw = explode(".", str_replace("/dev/", "", $config['mounts']['mount'][$i]['mdisk']));    // get rid of .eli .nop etc and /dev/
                fwrite($eguiconfig, "MOUNT{$i}DISK0={$device_raw[0]}"."\n");            // set disk to mdisk if there is no raid
            }
        }
    }
    $i1 = $i;                                                                           // use $i1 to continue the mount index for pools
    exec("geom label status -s", $rawdatageom);
    exec("gpart status -s", $rawdatagpart);
    if (is_array($config['zfs']) && is_array($config['zfs']['pools']) && is_array($config['zfs']['pools']['pool'])) {       // get pools
        for ($i = 0; $i < count($config['zfs']['pools']['pool']); ++$i) {
            fwrite($eguiconfig, "MOUNT{$i1}={$config['zfs']['pools']['pool'][$i]['name']}"."\n");                           // get pool name
            $disk_count = 0;          // necessary if there is more than one vdevice per pool to get consecutive disknumber in CONFIG2
                for ($j = 0; $j < count($config['zfs']['pools']['pool'][$i]['vdevice']); ++$j) {
                    fwrite($eguiconfig, "MOUNT{$i1}VDEVICE{$j}={$config['zfs']['pools']['pool'][$i]['vdevice'][$j]}"."\n"); // get pool vdevices
                    if (is_array($config['zfs']) && is_array($config['zfs']['vdevices']) && is_array($config['zfs']['vdevices']['vdevice'])) {
                        for ($k = 0; $k < count($config['zfs']['vdevices']['vdevice']); ++$k) {                             // get vdevice
                    		if (preg_match("/^{$config['zfs']['pools']['pool'][$i]['vdevice'][$j]}$/", $config['zfs']['vdevices']['vdevice'][$k]['name'])) {
                                for ($l = 0; $l < count($config['zfs']['vdevices']['vdevice'][$k]['device']); ++$l) {
                                    $device_raw = explode(".", str_replace("/dev/", "", $config['zfs']['vdevices']['vdevice'][$k]['device'][$l]));    // get rid of .eli .nop etc and /dev/
                                    $dev = $device_raw[0];
                                    foreach($rawdatageom as $key) {                                                         // get disks on GPT
                                        $key = trim($key);
                                        $device = preg_split("/[\s]+/", $key);
                                        if (strcmp($dev, $device[0]) == 0) { $dev = $device[2]; 
                                        }
                                    }
                                    foreach($rawdatagpart as $key) {                                                        // get disks on label and/or partitions
                                        $key = trim($key);
                                        $device = preg_split("/[\s]+/", $key);
                                        if (strcmp($dev, $device[0]) == 0) { $dev = $device[2];
                                        }
                                    }
                                    fwrite($eguiconfig, "MOUNT{$i1}DISK{$disk_count}={$dev}"."\n");                         // get vdevice disks
                                    ++$disk_count;
                                }
                            }
                        }
                    }
                }
            ++$i1;
        }
        if (isset($config['extended-gui']['zfs'])) {                                                            // put zfs datasets and volumes
            if (is_array($config['zfs']['datasets']) && is_array($config['zfs']['datasets']['dataset'])) {      // get datasets
                for ($i = 0; $i < count($config['zfs']['datasets']['dataset']); ++$i) {
                    $config['extended-gui']['shares'][$config['zfs']['datasets']['dataset'][$i]['name']] = "{$config['zfs']['datasets']['dataset'][$i]['pool'][0]}/{$config['zfs']['datasets']['dataset'][$i]['name']}";
                    fwrite($eguiconfig, "MOUNT{$i1}={$config['zfs']['datasets']['dataset'][$i]['pool'][0]}/{$config['zfs']['datasets']['dataset'][$i]['name']}"."\n");    // get dataset name
                    fwrite($eguiconfig, "MOUNT{$i1}DISK0=ds{$i}"."\n");                                         // set dummy disk
                    ++$i1;
                }
            }   // get datasets
            if (is_array($config['zfs']['volumes']) && is_array($config['zfs']['volumes']['volume'])) {         // get volumes
                for ($i = 0; $i < count($config['zfs']['volumes']['volume']); ++$i) {
                    $config['extended-gui']['shares'][$config['zfs']['volumes']['volume'][$i]['name']] = "{$config['zfs']['volumes']['volume'][$i]['pool'][0]}/{$config['zfs']['volumes']['volume'][$i]['name']}";
                    fwrite($eguiconfig, "MOUNT{$i1}={$config['zfs']['volumes']['volume'][$i]['pool'][0]}/{$config['zfs']['volumes']['volume'][$i]['name']}"."\n");    // get volume name
                    fwrite($eguiconfig, "MOUNT{$i1}DISK0=vol{$i}"."\n");                                        // set dummy disk
                    ++$i1;
                }
            }   // get volumes
        }   // get datasets & volumes
    }   // get pools
    $i = $i1;
    if (isset($config['extended-gui']['boot'])) {
        $config['extended-gui']['shares']['A_OS'] = 'A_OS';
        $mount_device = str_replace("/dev/", "", exec("df | awk '$6 ~ /\/$/ {print $1}'"));
        if (!empty($mount_device)) {
            foreach($rawdatageom as $key) {                                                         // get disks on GPT
                $key = trim($key);
                $device = preg_split("/[\s]+/", $key);
                if (strcmp($mount_device, $device[0]) == 0) { $mount_device = $device[2];
                }
            }
            foreach($rawdatagpart as $key) {                                                        // get disks on label and/or partitions
                $key = trim($key);
                $device = preg_split("/[\s]+/", $key);
                if (strcmp($mount_device, $device[0]) == 0) { $mount_device = $device[2];
                }
            }
            foreach($rawdatagpart as $key) {                                                        // get disks on label and/or partitions
                $key = trim($key);
                $device = preg_split("/[\s]+/", $key);
                if (strcmp($mount_device, $device[0]) == 0) { $mount_device = $device[2];
                }
            }
            fwrite($eguiconfig, "MOUNT{$i}=A_OS"."\n");
            fwrite($eguiconfig, "MOUNT{$i}DISK0={$mount_device}"."\n");
            ++$i;
        }
    }
    if (isset($config['extended-gui']['varfs'])) {
        $config['extended-gui']['shares']['A_VAR'] = 'A_VAR';
        $mount_device = str_replace("/dev/", "", exec("df | awk '$6 ~ /\/var$/ {print $1}'"));
        if (!empty($mount_device)) {
            fwrite($eguiconfig, "MOUNT{$i}=A_VAR"."\n");
            fwrite($eguiconfig, "MOUNT{$i}DISK0={$mount_device}"."\n");
            ++$i;
        }
    }
    if (isset($config['extended-gui']['usrfs'])) {
        $config['extended-gui']['shares']['A_USR'] = 'A_USR';
        $mount_device = str_replace("/dev/", "", exec("df | awk '$6 ~ /\/usr\/local$/ {print $1}'"));
        if (!empty($mount_device)) {
            fwrite($eguiconfig, "MOUNT{$i}=A_USR"."\n");
            fwrite($eguiconfig, "MOUNT{$i}DISK0={$mount_device}"."\n");
            ++$i;
        }
    }
fclose($eguiconfig);
$nextMP = fopen("/var/scripts/nextMP", "w");                                                       // for USB mountpoints
fwrite($nextMP, "NEXT_MP={$i}"."\n");
fclose($nextMP);
write_config();
//mwexec("logger extended-gui: CONFIG2 created");
?>
