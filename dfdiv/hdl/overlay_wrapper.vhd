library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity rpDUT is

  port (
    m_axis_0_tdata      : out STD_LOGIC_VECTOR (31 downto 0);
    m_axis_0_tlast      : out STD_LOGIC;
    m_axis_0_tready     : in  STD_LOGIC;
    m_axis_0_tvalid     : out STD_LOGIC;
    s_axis_0_tdata      : in  STD_LOGIC_VECTOR (31 downto 0);
    s_axis_0_tlast      : in  STD_LOGIC;
    s_axis_0_tready     : out STD_LOGIC;
    s_axis_0_tvalid     : in  STD_LOGIC;
    timeClock_V_dout    : IN  STD_LOGIC_VECTOR (63 downto 0);
    timeClock_V_empty_n : IN  STD_LOGIC;
    timeClock_V_read    : OUT STD_LOGIC;
    clk_en              : in  STD_LOGIC;
    flagDone            : out STD_LOGIC;
    flagStart           : out STD_LOGIC;
    ap_clk              : IN  STD_LOGIC;
    ap_rst              : IN  STD_LOGIC);

end entity rpDUT;



architecture structure of rpDUT is

  component divider64 is
    port (
      ap_clk          : IN  STD_LOGIC;
      ap_rst_n        : IN  STD_LOGIC;
      slave_V_TDATA   : IN  STD_LOGIC_VECTOR (31 downto 0);
      slave_V_TVALID  : IN  STD_LOGIC;
      slave_V_TREADY  : OUT STD_LOGIC;
      master_V_TDATA  : OUT STD_LOGIC_VECTOR (31 downto 0);
      master_V_TVALID : OUT STD_LOGIC;
      master_V_TREADY : IN  STD_LOGIC);
  end component divider64;

  signal ap_rst_n : STD_LOGIC;
  signal ap_clk_i : STD_LOGIC;
  
  signal s_axis_0_tready_i : STD_LOGIC;
  signal m_axis_0_tvalid_i : STD_LOGIC;
  
begin

  ap_rst_n <= not ap_rst;
  
  m_axis_0_tlast <= '0';

  timeClock_V_read <= '0';
  flagDone <= '1' when s_axis_0_tready_i = '1' and s_axis_0_tvalid = '1' else
              '0';
  flagStart <= '1' when m_axis_0_tready = '1' and m_axis_0_tvalid_i = '1' else
              '0';

  ap_clk_i <= ap_clk when clk_en = '1' else
              '0';
  
  s_axis_0_tready <= s_axis_0_tready_i;
  m_axis_0_tvalid <= m_axis_0_tvalid_i;
    
  divider64_1: divider64
    port map (
      ap_clk          => ap_clk_i,
      ap_rst_n        => ap_rst_n,
      slave_V_TDATA   => s_axis_0_tdata,
      slave_V_TVALID  => s_axis_0_tvalid,
      slave_V_TREADY  => s_axis_0_tready_i,
      master_V_TDATA  => m_axis_0_tdata,
      master_V_TVALID => m_axis_0_tvalid_i,
      master_V_TREADY => m_axis_0_tready);

  
end structure;
