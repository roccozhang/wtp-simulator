<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<title>pfSense-Jie.HiWiFi.net - Interfaces: VLAN</title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<link rel=”apple-touch-icon” href="http://admin:G9923142@192.168.154.131/%E2%80%9D/themes/nervecenter/apple-touch-icon.png%E2%80%9D/">
                <link rel="stylesheet" href="themes/nervecenter/all.css" media="all" />
        	<link rel="stylesheet" type="text/css" href="niftycssprintCode.css" media="print" />
	<script type="text/javascript">var theme = "nervecenter"</script>
	<script type="text/javascript" src="themes/nervecenter/loader.js"></script>


</head>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">

<div id="wrapper">

	<div id="header">
		<div id="header-left"><a href="index.php" id="status-link"><img src="themes/nervecenter/images/transparent.gif" border="0"></img></a></div>
		<div id="header-right">
			<div class="container">
				<div class="left">webConfigurator</div>
				<div class="right">
					<div id="hostname">
						pfSense-Jie.HiWiFi.net					</div>
				</div>
			</div>
		</div>
	</div> <!-- Header DIV -->
	<div id="content">
		<div id="left">
			<div id="navigation" style="z-index:1000">  
				<ul id="menu">
					<li class="firstdrop">
						<div>System</div>
						<ul class="subdrop">
							<li><a href="system_advanced.php" class="navlnk">Advanced</a></li>
							<li><a href="system_firmware.php" class="navlnk">Firmware</a></li>
							<li><a href="system.php" class="navlnk">General Setup</a></li>
													<li><a href="pkg_mgr.php" class="navlnk">Packages</a></li>
													<li><a href="wizard.php@xml=setup_wizard.xml" class="navlnk">Setup wizard</a></li>
							<li><a href="system_routes.php" class="navlnk">Static routes</a></li>
						</ul>
					</li>
					<li class="drop">
						<div>Interfaces</div>
						<ul class="subdrop">
							<li><a href="interfaces_assign.php" class="navlnks">(assign)</a></li>							<li><a href="interfaces_wan.php" class="navlnk">WAN</a></li>
							<li><a href="interfaces_lan.php" class="navlnk">LAN</a></li>
																				</ul>
					</li>
					<li class="drop">
						<div>Firewall</div>
						<ul class="subdrop">
							<li><a href="firewall_aliases.php" class="navlnk">Aliases</a></li>
							<li><a href="firewall_nat.php" class="navlnk">NAT</a></li>
							<li><a href="firewall_rules.php" class="navlnk">Rules</a></li>
							<li><a href="firewall_schedule.php" class="navlnk">Schedules</a></li>
							<li><a href="wizard.php@xml=traffic_shaper_wizard.xml" class="navlnk">Traffic Shaper</a></li>
							<li><a href="firewall_virtual_ip.php" class="navlnk">Virtual IPs</a></li>
													</ul>
					</li>
					<li class="drop">
						<div>Services</div>
						<ul class="subdrop">
							<li><a href="services_captiveportal.php" class="navlnk">Captive portal</a></li>
							<li><a href="services_dnsmasq.php" class="navlnk">DNS forwarder</a></li>
							<li><a href="services_dhcp_relay.php" class="navlnk">DHCP relay</a></li>
							<li><a href="services_dhcp.php" class="navlnk">DHCP server</a></li>
							<li><a href="services_dyndns.php" class="navlnk">Dynamic DNS</a></li>
							<li><a href="load_balancer_pool.php" class="navlnk">Load Balancer</a></li>
							<li><a href="pkg_edit.php@xml=olsrd.xml&amp;id=0" class="navlnk">OLSR</a></li>
							<li><a href="vpn_pppoe.php" class="navlnk">PPPoE Server</a></li>
							<li><a href="pkg_edit.php@xml=routed%252Frouted.xml&amp;id=0" class="navlnk">RIP</a></li>
							<li><a href="services_snmp.php" class="navlnk">SNMP</a></li>
							<li><a href="pkg_edit.php@xml=miniupnpd.xml&amp;id=0" class="navlnk">UPnP</a></li>
							<li><a href="pkg_edit.php@xml=openntpd.xml&amp;id=0" class="navlnk">OpenNTPD</a></li>
							<li><a href="services_wol.php" class="navlnk">Wake on LAN</a></li>
													</ul>
					</li>
					<li class="drop">
						<div>VPN</div>
						<ul class="subdrop">
							<li><a href="vpn_ipsec.php" class="navlnk">IPsec</a></li>
							<li><a href="pkg.php@xml=openvpn.xml" class="navlnk">OpenVPN</a></li>
							<li><a href="vpn_pptp.php" class="navlnk">PPTP</a></li>
													</ul>
					</li>
					<li class="drop">
						<div>Status</div>
						<ul class="subdrop">
														<li><a href="carp_status.php" class="navlnk">CARP (failover)</a></li>
							<li><a href="diag_dhcp_leases.php" class="navlnk">DHCP leases</a></li>
							<li><a href="status_filter_reload.php" class="navlnk">Filter Reload Status</a></li>
							<li><a href="status_interfaces.php" class="navlnk">Interfaces</a></li>
							<li><a href="diag_ipsec.php" class="navlnk">IPsec</a></li>
							<li><a href="status_slbd_pool.php" class="navlnk">Load Balancer</a></li>
														<li><a href="diag_pkglogs.php" class="navlnk">Package logs</a></li>
														<li><a href="status_queues.php" class="navlnk">Queues</a></li>
							<li><a href="status_rrd_graph.php" class="navlnk">RRD Graphs</a></li>
							<li><a href="status_services.php" class="navlnk">Services</a></li>
							<li><a href="index.php" class="navlnk">System</a></li>
							<li><a href="diag_logs.php" class="navlnk">System logs</a></li>
							<li><a href="status_graph.php@if=wan" class="navlnk">Traffic graph</a></li>
							<li><a href="status_upnp.php" class="navlnk">UPnP</a></li>
																				</ul>
					</li>
					<li class="lastdrop">
						<div>Diagnostics</div>
						<ul id="diag" class="subdrop">
							<li><a href="diag_arp.php" class="navlnk">ARP Tables</a></li>
							<li><a href="diag_backup.php" class="navlnk">Backup/Restore</a></li>
							<li><a href="exec.php" class="navlnk">Command Prompt</a></li>
							<li><a href="edit.php" class="navlnk">Edit File</a></li>
							<li><a href="diag_defaults.php" class="navlnk">Factory defaults </a></li>
							<li><a href="halt.php" class="navlnk">Halt system</a></li>
							<li><a href="diag_ping.php" class="navlnk">Ping</a></li>
							<li><a href="reboot.php" class="navlnk">Reboot system</a></li>
							<li><a href="diag_routes.php" class="navlnk">Routes</a></li>
							<li><a href="diag_dump_states.php" class="navlnk">States</a></li>
							<li><a href="diag_traceroute.php" class="navlnk">Traceroute</a></li>
							<li><a href="diag_packet_capture.php" class="navlnk">Packet Capture</a></li>
																				</ul>
					</li>
				</ul>
			</div>

		</div> <!-- Left DIV -->

		<div id="right">


<p class="pgtitle">Interfaces: VLAN</p>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr><td>
<table cellpadding='0' cellspacing='0'>
 <tr height='1'>
  <td bgcolor='#777777' onClick="document.location='interfaces_assign.php'" style="cursor: pointer;"><div id='tabdeactive0'></div></td>
  <td bgcolor='#EEEEEE' onClick="document.location='interfaces_vlan.php'" style="cursor: pointer;"><div id='tabactive'></div></td>
</tr>
<tr>
  <td bgcolor='#777777' onClick="document.location='interfaces_assign.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='interfaces_assign.php'><font color='white'>Interface assignments</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#EEEEEE' onClick="document.location='interfaces_vlan.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;VLANs&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
</tr>
<tr height='5px'>
  <td bgcolor='#777777' onClick="document.location='interfaces_assign.php'" style="cursor: pointer;"></td>
  <td bgcolor='#EEEEEE' onClick="document.location='interfaces_vlan.php'" style="cursor: pointer;"></td>
 </tr>
</table>
<script type="text/javascript">NiftyCheck();
Rounded("div#tabactive","top","#FFF","#EEEEEE","smooth");
Rounded("div#tabdeactive0","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive1","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive2","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive3","top","#FFF","#777777","smooth");
</script>  </td></tr>
  <tr>
    <td>
	<div id="mainarea">
	<table class="tabcont" width="100%" border="0" cellpadding="0" cellspacing="0">
                <tr>
                  <td width="20%" class="listhdrr">Interface</td>
                  <td width="20%" class="listhdrr">VLAN tag</td>
                  <td width="50%" class="listhdr">Description</td>
                  <td width="10%" class="list"></td>
				</tr>
			                  <tr>
                  <td class="list" colspan="3">&nbsp;</td>
                  <td class="list"> <a href="interfaces_vlan_edit.php"><img src="themes/nervecenter/images/icons/icon_plus.gif" width="17" height="17" border="0"></a></td>
				</tr>
				<tr>
				<td colspan="3" class="list"><p class="vexpl"><span class="red"><strong>
				  Note:<br>
				  </strong></span>
				  Not all drivers/NICs support 802.1Q VLAN tagging properly. On cards that do not explicitly support it, VLAN tagging will still work, but the reduced MTU may cause problems. See the pfSense handbook for information on supported cards. </p>
				  </td>
				<td class="list">&nbsp;</td>
				</tr>
              </table>
	      </div>
	</td>
	</tr>
</table>
                </div> <!-- Right DIV -->
        </div> <!-- Content DIV -->
        <div id="footer">
			<a target="_blank" href="http://www.pfsense.org/?gui12" class="redlnk">pfSense</a> is &copy;
			 2004 - 2009 by <a href="http://www.bsdperimeter.com" class="tblnk">BSD Perimeter LLC</a>. All Rights Reserved.
			[<a href="license.php" class="tblnk">view license</a>] 
			<br/>
			[<a target="_blank" href="https://portal.pfsense.org/?guilead=true" class="tblnk">Commercial Support Available</a>]
		</div> <!-- Footer DIV -->
</div> <!-- Wrapper Div -->
<script type="text/javascript" src="themes/nervecenter/bottom-loader.js"></script>

</body>
</html>
