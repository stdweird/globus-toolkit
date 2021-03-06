# Copyright 1999-2009 University of Chicago
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""
Object definition for processing Java WS Core (version 1) usage packets.
"""

from globus.usage.iptimemonitorpacket import IPTimeMonitorPacket

class JavaWSCoreV1Packet(IPTimeMonitorPacket):
    """
    Packet parser and handler for the JavaWS Core V1 packet format. This
    format was used in GT 4.0.0 - GT 4.0.2
    """
    def __init__(self, address, packet):
        IPTimeMonitorPacket.__init__(self, address, packet)
        [self.container_id, self.container_type, self.event_type] = \
                self.unpack("ihh")

    insert_statement = '''
            INSERT INTO java_ws_core_packets(
                component_code,
                version_code,
                send_time,
                ip_address,
                container_id,
                container_type,
                event_type)
            VALUES (%s, %s, %s, %s, %s, %s, %s)'''

    def values(self, dbclass):
        """
        Return a values tuple which matches the parameters in the
        class's insert_statement.

        Arguments:
        self -- A JavaWSCoreV1Packet object

        Returns:
        Tuple containing
            (component_code, version_code, send_time,
            ip_address, container_id, container_type, event_type)

        Returns:
        None.

        """
        return (
            self.component_code,
            self.packet_version,
            dbclass.Timestamp(*self.send_time),
            self.ip_address,
            self.container_id,
            self.container_type,
            self.event_type)
